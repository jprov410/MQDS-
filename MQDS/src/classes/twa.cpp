//
// Created by Justin Provazza on 12/8/18.
//
#include <iostream>
#include <complex>
#include <cmath>
#include "MQDS/twa.h"
#include "MQDS/system.h"
#include "MQDS/bath.h"
#include "MQDS/calculation.h"
#include "MQDS/io.h"
#include "MQDS/universe.h"
#include "MQDS/units.h"
#include "MQDS/constants.h"


void MQDS::TWA::initialize_method(std::unique_ptr<System> & system,
                                   std::unique_ptr<Bath> & bath,
                                   MQDS::IO & io)
{
    const int bath_copies = 1;
    const int system_copies = 1;
    bath->initialize_phase_space(bath_copies,io.nbath(),io.nosc());
    system->initialize_mapping_variables(system_copies,io.nstate());
    return;
}

std::vector<Eigen::MatrixXcd>
MQDS::TWA::calculate_reduced_density_matrix(std::unique_ptr<MQDS::System> & system,
                                             std::unique_ptr<MQDS::Bath> & bath,
                                             MQDS::IO & io,
                                             MQDS::Universe & pe)
{
    // ALLOCATE REDUCED DENSITY MATRIX TO CALCULATE WITH PLDM
    allocate_redmat(io);
    // CALCULATE BETA = (1/K_B*T), AND DT FOR A TIME-STEP
    const double beta = 1.0 / (io.temperature() * Units::conversion(Units::kelvin,Units::atomic_energy));
    const double dt = io.runtime() * Units::conversion(Units::femtoseconds,Units::atomic_time)/io.nstep();
    std::complex<double> traj_per_proc(io.ntraj()/pe.num_procs(),0.0);

    // LOOP OVER ENSEMBLE OF TRAJECTORIES
    for (int itraj=0; itraj<io.ntraj()/pe.num_procs(); ++itraj)
    {
        // GATHER ALL INITIAL CONDITIONS FOR THE TRAJECTORY
        system->gaussian_mapping_initial_conditions(0.0,std::sqrt(0.5));
        system->assign_initial_trajectory_weight
                (initial_trajectory_weight(system,io.initstate(),io.initstatet()));

        // ASSUMES BOLTZMANN INITIAL CONDITIONS
        bath->bare_boltzmann_wigner_initial_conditions(beta);

        // INITIALIZE TIME DIMENSION COUNTER
        int itime=0;
        redmat_[itime] = redmat_[itime] + redmat_function(system);
        for (int istep=1; istep<io.nstep()+1; ++istep)
        {
            // ADVANCE ALL DOF BY A TIME-STEP
            propagate(system,bath,dt,io.nlit());

            // IF INTEGER MULTIPLE OF IO.DUMP(), CALCULATE REDUCED DENSITY MATRIX
            if (istep % io.dump() == 0)
            {
                itime+=1;
                redmat_[itime] = redmat_[itime] + redmat_function(system);
            }
        }
    }

    // AVERAGE RESULT OVER NUMBER OF TRAJECTORIES ON THIS PROCESSOR
    for (int itime=0; itime<redmat_.size(); ++itime)
    {
        for (int istate=0; istate<io.nstate(); ++istate)
        {
            for (int jstate=0; jstate<io.nstate(); ++jstate)
            {
                redmat_[itime](istate,jstate)=redmat_[itime](istate,jstate)
                                               /(traj_per_proc);
            }
        }
    }

    return redmat_;
}

// PROPAGATION USING THE TWA EQUATIONS OF MOTION
void MQDS::TWA::propagate(std::unique_ptr<System> & system,
                           std::unique_ptr<Bath> & bath,
                           const double & dt,
                           const int & nlit)
{

    //position half-step
    bath->advance_position(0.5*dt);

    //mapping full-step, forward mapping and backward mapping
    system->advance_mapping_variables(0,what_system_feels(0,system,bath),dt,nlit);

    //momentum full-step
    bath->advance_momentum(what_bath_feels(system,bath),dt);

    //position half-step
    bath->advance_position(0.5*dt);

    return;
}

// WHAT THE BATH DYNAMICS IS GOVERENED BY IN PLDM
std::vector<Eigen::MatrixXd> MQDS::TWA::what_bath_feels(std::unique_ptr<System> & system,
                                                         std::unique_ptr<Bath> & bath)
{
    const int bath_copies=1;
    std::vector<Eigen::MatrixXd> pldm_what_bath_feels;
    pldm_what_bath_feels.resize(bath_copies);

    pldm_what_bath_feels[0].resize(system->position_map()[0].size(), system->position_map()[0].size());
    // vector is of length bath_copies, matrix is nstate x nstate
    for (int istate=0; istate<system->position_map()[0].size(); ++istate)
    {
        for (int jstate = 0; jstate < system->position_map()[0].size(); ++jstate)
        {
            if (istate==jstate) {
                pldm_what_bath_feels[0](istate, jstate) = 0.5 * (system->position_map()[0](istate)
                                                                 * system->position_map()[0](jstate)
                                                                 + system->momentum_map()[0](istate)
                                                                   * system->momentum_map()[0](jstate) - 1);
            }
            else
            {
                pldm_what_bath_feels[0](istate,jstate) = 0.5 * (system->position_map()[0](istate)
                                                                * system->position_map()[0](jstate)
                                                                + system->momentum_map()[0](istate)
                                                                  * system->momentum_map()[0](jstate));
            }
        }
    }
    return pldm_what_bath_feels;
}

// WHAT THE SYSTEM (MAPPING VARIABLE) DYNAMICS IS CONTROLLED BY IN PLDM
Eigen::MatrixXd MQDS::TWA::what_system_feels(const int &icopy,
                                              std::unique_ptr<System> & system,
                                              std::unique_ptr<Bath> & bath)
{
    // ONLY ONE COPY OF BATH FOR PLDM
    Eigen::MatrixXd pldm_what_system_feels;
    pldm_what_system_feels.resize(system->position_map()[0].size(), system->position_map()[0].size());

    for (int istate = 0; istate < system->position_map()[0].size(); ++istate) {
        for (int jstate = 0; jstate < system->position_map()[0].size(); ++jstate) {
            pldm_what_system_feels(istate, jstate) = system->hamiltonian()(istate, jstate)
                                                     + bath->sb_portion_of_hamiltonian(icopy, istate, jstate);
        }
    }
    return pldm_what_system_feels;
}

// CALCULATE THE REDUCED DENSITY MATRIX WITH TWA
Eigen::MatrixXcd
MQDS::TWA::redmat_function(std::unique_ptr<System> & system)
{
    Eigen::MatrixXcd temp(system->position_map()[0].size(), system->position_map()[0].size());

    double gauss_factor=1.0;
    for (int istate = 0; istate < system->position_map()[0].size(); ++istate)
    {
        gauss_factor *= std::exp(- std::pow(system->position_map()[0](istate),2)
                                 - std::pow(system->momentum_map()[0](istate),2));
    }


    for (int istate = 0; istate < system->position_map()[0].size(); ++istate) {
        for (int jstate = 0; jstate < system->position_map()[0].size(); ++jstate) {
            if (istate == jstate)
            {
                temp(istate, jstate) = system->initial_trajectory_weight() * gauss_factor
                                       * (std::pow(system->position_map()[0](istate),2)
                                          + std::pow(system->momentum_map()[0](istate),2)-0.5);
            }
            else
            {
                temp(istate, jstate) = system->initial_trajectory_weight() * gauss_factor
                                       * (system->position_map()[0](istate)
                                          + MQDS::Constants::eye * system->momentum_map()[0](istate))
                                       * (system->position_map()[0](jstate)
                                          - MQDS::Constants::eye * system->momentum_map()[0](jstate));
            }
        }
    }
    return temp;
}

// GET THE INITIAL TRAJECTORY WEIGHT
std::complex<double> MQDS::TWA::initial_trajectory_weight(std::unique_ptr<System> & system,
                                                           const int &initstate,
                                                           const int &initstatet)
{

    if (initstate==initstatet)
    {
        return std::pow(2.0,2*system->position_map()[0].size())
               * (std::pow(system->position_map()[0](initstate),2)
                  + std::pow(system->momentum_map()[0](initstate),2) - 0.5);
    }
    else
    {
        return std::pow(2.0,2*system->position_map()[0].size())
               * (system->position_map()[0](initstate) - Constants::eye * system->momentum_map()[0](initstate))
               * (system->position_map()[0](initstatet) + Constants::eye * system->momentum_map()[0](initstatet));
    }

}