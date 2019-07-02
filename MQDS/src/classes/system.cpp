//
// Created by Justin Provazza on 10/9/18.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "MQDS/system.h"
#include "MQDS/io.h"
#include "MQDS/units.h"
#include "MQDS/random.h"

void MQDS::System::read_input(int const &nstate)
{
    hamiltonian_.resize(nstate,nstate);
    std::ifstream sys_ham_input;
    int i=0,j=0;
    double element;

    sys_ham_input.open("systemhamiltonian.in");
    if (sys_ham_input.is_open())
    {
        for (std::string line; std::getline(sys_ham_input, line);)
        {
            std::istringstream ss(line);
            i = 0;
            while(ss >> element)
            {
                hamiltonian_(j,i) = element *
                                    MQDS::Units::conversion(MQDS::Units::wavenumber,MQDS::Units::atomic_energy);
                i++;
            }
            j++;
        }
        if (j != nstate || i != nstate)
        {
            MQDS::IO::write_error("Input system Hamiltonian matrix size doesn't match nstate");
        }
    }
    else
    {
        MQDS::IO::write_error("Unable to find systemhamiltonian.in file");
    }
    sys_ham_input.close();
}

void MQDS::System::initialize_mapping_variables(const int &ncopies, const int &nstate)
{
    position_map_.resize(ncopies);
    momentum_map_.resize(ncopies);

    for (int icopy=0; icopy<ncopies; ++icopy)
    {
        position_map_[icopy].resize(nstate);
        momentum_map_[icopy].resize(nstate);
    }
    return;
}

void MQDS::System::get_mapping_initial_conditions(const double &mean,
                                                  const double &sigma,
                                                  const int &initstate,
                                                  const int &initstatet)
{
    for (int icopy=0; icopy<position_map_.size(); ++icopy)
    {
        for (int istate=0; istate<position_map_[0].size(); ++istate)
        {
            position_map_[icopy](istate) = MQDS::Random::gaussian_random_number(mean, sigma);
            momentum_map_[icopy](istate) = MQDS::Random::gaussian_random_number(mean, sigma);
        }
    }
    initial_trajectory_weight_=get_initial_mapping_weight(initstate,initstatet);
    return;
}

void MQDS::System::advance_mapping_variables(const int &system_copy,
                                       const Eigen::MatrixXd &ham,
                                       const double &total_timestep,
                                       const int &nstep)
{
    const double dt = total_timestep/nstep;
    Eigen::VectorXd dxdt(position_map()[0].size());
    Eigen::VectorXd dpdt(position_map()[0].size());

    for (int istep=0; istep<nstep; ++istep)
    {

        //CALCULATE FIRST TIME DERIVATIVES
        for (int istate=0; istate<position_map()[0].size(); ++istate)
        {
            dxdt(istate)=0.0; dpdt(istate)=0.0;
            for (int jstate=0; jstate<position_map()[0].size(); ++jstate)
            {
                dxdt(istate)+= momentum_map()[system_copy](jstate)*ham(istate,jstate);
                dpdt(istate)+= - position_map()[system_copy](jstate)*ham(istate,jstate);
            }
        }

        /*
        //CALCULATE SECOND TIME DERIVATIVE
        for (int istate=0; istate<position_map_[0].size(); ++istate)
        {
            for (int jstate=0; jstate<position_map_[0].size(); ++jstate)
            {
                d2xdt2(istate) += dpdt(jstate)*ham(istate,jstate);
            }
        }*/

        //

        //ADVANCE THE MAPPING VARIABLES
        for (int istate=0; istate<position_map_[0].size(); ++istate)
        {
            position_map_[system_copy](istate) += dxdt(istate)*dt; //+ 0.5*d2xdt2(istate)*dt*dt;
            momentum_map_[system_copy](istate) += dpdt(istate)*dt;
        }


    }
    return;
}