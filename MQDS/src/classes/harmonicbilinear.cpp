//
// Created by Justin Provazza on 12/8/18.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <MQDS/constants.h>
#include "MQDS/harmonicbilinear.h"
#include "MQDS/bath.h"
#include "MQDS/io.h"
#include "MQDS/random.h"
#include "MQDS/units.h"
#include "MQDS/system.h"

MQDS::HarmonicBilinear::HarmonicBilinear()
{

}

void MQDS::HarmonicBilinear::read_input(const int &nbath, const int &nosc, const int &nstate)
{
    std::stringstream filename;
    std::ifstream spec_den_input;
    double element;
    std::string line;

    //RESIZE MATRICES FOR EACH BATH
    frequency_.resize(nbath);
    coupling_.resize(nbath);
    sys_bath_coupling_.resize(nbath);
    for (int ibath=0; ibath<nbath; ++ibath)
    {
        frequency_[ibath].resize(nosc);
        coupling_[ibath].resize(nosc);
        sys_bath_coupling_[ibath].resize(nstate,nstate);
    }

    for (int ibath=0; ibath<nbath; ++ibath)
    {
        std::vector<double> j_of_omega, omega, lambda_of_omega;
        Eigen::MatrixXd temp_matrix(nstate,nstate);

        //Find current spectral density input file name
        filename << "spectraldensity"<< ibath+1 << ".in";
        spec_den_input.open(filename.str());

        //Read in sys_bath_coupling (nstate X nstate)
        if (spec_den_input.is_open())
        {
            for (int istate=0; istate<nstate; ++istate)
            {
                std::getline(spec_den_input, line);
                std::istringstream ss(line);
                int jstate=0;
                while (ss >> element)
                {
                    temp_matrix(istate,jstate) = element;
                    jstate++;
                }
            }
            sys_bath_coupling_[ibath] = temp_matrix;
        }
        else
        {
            MQDS::IO::write_error("Unable to find all spectral density files, expected " + std::to_string(nbath));
        }

        //Read in omega and j_of_omega.... compute lambda_of_omega and normalization
        for (std::string sd_line; std::getline(spec_den_input, sd_line);)
        {
            std::istringstream ss(sd_line);
            double w, jw;
            ss >> w;
            ss >> jw;
            omega.push_back(w * MQDS::Units::conversion
                    (MQDS::Units::wavenumber,
                     MQDS::Units::atomic_angular_frequency));
            j_of_omega.push_back(jw* MQDS::Units::conversion
                    (MQDS::Units::wavenumber,
                     MQDS::Units::atomic_energy));
        }

        //Make sure the size of input spectral density is larger than nosc
        if (omega.size() < nosc)
        {
            MQDS::IO::write_error("nosc is greater than number of points provided in spectral density input");
        }

        //Compute cumulative reorganization energy \Lambda(\Omega) = \frac{1}{\pi} int_0^\Omega d\omega j(\omega) / \omega
        double dw = omega[1]-omega[0];
        if (omega[0]==0.0)
        {
            lambda_of_omega.push_back(0.0);
        }
        else
        {
            lambda_of_omega.push_back(dw * j_of_omega[0] / omega[0] );
        }
        for (int ifreq=1; ifreq<j_of_omega.size(); ++ifreq)
        {
            lambda_of_omega.push_back
                    (lambda_of_omega[ifreq-1]+ dw * j_of_omega[ifreq]/omega[ifreq]);
        }
        j_of_omega.clear();

        double normalization = nosc / lambda_of_omega.back();
        for (int ifreq=0; ifreq<lambda_of_omega.size(); ++ifreq)
        {
            lambda_of_omega[ifreq] = lambda_of_omega[ifreq] * normalization;
        }

        int sampled_mode=0;
        for (int iosc=0; iosc<nosc-1; ++iosc)
        {
            while (lambda_of_omega[sampled_mode] <= iosc)
            {
                sampled_mode+=1;
            }
            frequency_[ibath](iosc)=omega[sampled_mode];
            coupling_[ibath](iosc)=sqrt(2.0 / (MQDS::Constants::pi * normalization)) * omega[sampled_mode];
        }
        frequency_[ibath](nosc-1)=omega.back();
        coupling_[ibath](nosc-1)=sqrt(2.0 / (MQDS::Constants::pi * normalization)) * omega.back();


        //Clean-up after finished with current file
        spec_den_input.close();
        filename.str("");
        omega.clear();
        lambda_of_omega.clear();
    } //END LOOP OVER BATHS

    return;
}

void MQDS::HarmonicBilinear::bare_boltzmann_wigner_initial_conditions(const double &beta)
{
    for (int icopy=0; icopy<momentum_.size(); ++icopy)
    {
        for (int ibath=0; ibath<momentum_[0].size(); ++ibath)
        {
            for (int iosc=0; iosc<momentum_[0][0].size(); ++iosc)
            {
                // CALCULATE STD DEV FROM WIGNER TRANSFORMED BOLTZMANN OPERATOR FOR SIMPLE H.O.
                momentum_[icopy][ibath](iosc) =
                        std::sqrt(frequency_[ibath](iosc)/(2.0*std::tanh(0.5*beta*frequency_[ibath](iosc))));
                position_[icopy][ibath](iosc) = momentum_[icopy][ibath](iosc) / frequency_[ibath](iosc);
                // NOW MULTIPLY BY GAUSSIAN (PSEUDO)RANDOM NUMBER CENTERED AT 0 (with unit variance because calculated above)
                momentum_[icopy][ibath](iosc) = momentum_[icopy][ibath](iosc)
                                                * MQDS::Random::gaussian_random_number(0.0,1.0);
                position_[icopy][ibath](iosc) = position_[icopy][ibath](iosc)
                                                * MQDS::Random::gaussian_random_number(0.0,1.0);
                //position_[icopy][ibath](iosc)=0.0;
                //momentum_[icopy][ibath](iosc)=0.0;
            }
        }
    }
}


void MQDS::HarmonicBilinear::compute_force(const std::vector<Eigen::MatrixXd> & method_specific_sb)
{
    for (int icopy=0; icopy < position_.size(); ++icopy)
    {
        for (int ibath=0; ibath < position_[0].size(); ++ibath)
        {
            for(int imode=0; imode<position_[0][0].size(); ++imode)
            {
                force_[icopy][ibath](imode) = - std::pow(frequency_[ibath](imode),2) * position_[icopy][ibath](imode);
                for (int istate=0; istate<std::sqrt(method_specific_sb[0].size()); ++ istate)
                {
                    for (int jstate=0; jstate<std::sqrt(method_specific_sb[0].size()); ++ jstate)
                    {
                        //SYS_BATH_COUPLING CONTROLS WHICH SYSTEM STATES A MODE FEELS
                        //METHOD_SPECIFIC_SB DETAILS HOW MODE FEELS THE STATES IT IS COUPLED TO
                        //E.G.) MAPPING VARIABLES IN PLDM
                        //COUPLING IS THE FORCE CONSTANT SAMPLED FROM SPECTRAL DENSITY
                        force_[icopy][ibath](imode) = force_[icopy][ibath](imode) -
                                                      coupling_[ibath](imode)
                                                      * sys_bath_coupling_[ibath](istate,jstate)
                                                      * method_specific_sb[icopy](istate,jstate);
                    }
                }
            }
        }
    }
    return;
}

double MQDS::HarmonicBilinear::sb_portion_of_hamiltonian(const int &bathcopy,
                                                         const int &istate,
                                                         const int &jstate)
{
    double bath_part_of_sb=0.0;
    for (int ibath=0; ibath<position()[bathcopy].size(); ++ibath)
    {
        for (int imode = 0; imode < position_[bathcopy][ibath].size(); ++imode)
        {
            bath_part_of_sb += sys_bath_coupling_[ibath](istate,jstate) * coupling_[ibath](imode)
                                * position_[bathcopy][ibath](imode);

        }
    }
    return bath_part_of_sb;
}