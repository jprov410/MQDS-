//
// Created by Justin Provazza on 12/8/18.
//
#include <iostream>
#include "MQDS/pldm.h"
#include "MQDS/system.h"
#include "MQDS/bath.h"
#include "MQDS/calculation.h"
#include "MQDS/io.h"



void MQDS::PLDM::calculate
        (std::unique_ptr<Calculation> & calculation,
         std::unique_ptr<System> & system,
         std::unique_ptr<Bath> & bath,
         MQDS::IO & io)
{
    system->read_input_hamiltonian(io.nstate());
    bath->read_spectral_density(io.nbath(),io.nosc(),io.nstate());


    return;
}