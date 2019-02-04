//
// Created by Justin Provazza on 12/8/18.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "MQDS/harmonicbilinear.h"
#include "MQDS/bath.h"
#include "MQDS/io.h"
#include "MQDS/random.h"
#include "MQDS/units.h"

MQDS::HarmonicBilinear::HarmonicBilinear()
{

}

std::vector<std::vector<double>> const MQDS::HarmonicBilinear::initial_conditions
        (const int &nbath,const int &nosc)
{
    position_.resize(nbath,std::vector<double>(nosc));
    momentum_.resize(nbath,std::vector<double>(nosc));

}

void MQDS::HarmonicBilinear::read_spectral_density(const int &nbath, const int &nosc, const int &nstate)
{
    frequency_.resize(nbath,std::vector<double>(nosc));
    coupling_.resize(nbath,std::vector<double>(nosc));
    sys_bath_coupling_.resize
            (nbath, std::vector<std::vector<double>>
                    (nstate,std::vector<double>(nstate)));


    std::stringstream filename;
    std::ifstream spec_den_input;
    double element;
    std::string line;
    std::vector<double> j_of_omega, omega;

    for (int ibath=0; ibath<nbath; ++ibath)
    {
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
                    sys_bath_coupling_[ibath][istate][jstate] = element;
                    jstate++;
                }
            }

        }
        else
        {
            MQDS::IO::write_error("Unable to find all spectral density files");
        }

        //Read in Frequency and J(omega)
        for (std::string sd_line; std::getline(spec_den_input, sd_line);)
        {
            std::istringstream ss(sd_line);
            double w_, jw_;
            ss >> w_;
            ss >> jw_;
            omega.push_back(w_ * MQDS::Units::conversion
                    (MQDS::Units::wavenumber,
                     MQDS::Units::atomic_angular_frequency));
            j_of_omega.push_back(jw_* MQDS::Units::conversion
                    (MQDS::Units::wavenumber,
                     MQDS::Units::atomic_energy));
        }

        //TODO: build distribution with current spectral density for sampling
        //Then fill the

        //Clean-up after finished with current file
        spec_den_input.close();
        filename.str("");
        omega.clear();
        j_of_omega.clear();
    }
    return;
}

void const MQDS::HarmonicBilinear::propagate_half_step()
{
    return;
}