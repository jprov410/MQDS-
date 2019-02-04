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

void MQDS::System::read_input_hamiltonian(int const &nstate)
{
    hamiltonian_.resize(nstate,std::vector<double>(nstate));
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
                hamiltonian_[j][i] = element
                                     * MQDS::Units::conversion(MQDS::Units::wavenumber,MQDS::Units::atomic_energy);
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