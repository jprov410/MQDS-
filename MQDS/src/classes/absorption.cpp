//
// Created by Justin Provazza on 12/8/18.
//

#include "MQDS/absorption.h"
#include "MQDS/calculation.h"
#include "MQDS/method.h"
#include "MQDS/system.h"
#include "MQDS/bath.h"
#include "MQDS/units.h"
#include <fstream>
#include <sstream>



void MQDS::Absorption::calculate
        (std::unique_ptr<Method> & method,
         std::unique_ptr<System> & system,
         std::unique_ptr<Bath> & bath,
         MQDS::IO & io,
         MQDS::Universe & pe)
{
    // READ THE NECESSARY INPUT DATA FOR DESCTRIPTION OF SYSTEM, BATH
    system->read_hamiltonian(io.nstate());
    system->read_dipole_matrix(io.nstate());
    bath->read_input(io.nbath(),io.nosc(),io.nstate());
    // ALLOCATE MEMORY FOR NECESSARY MATRICES/VECTORS FOR SYSTEM,BATH WITH METHOD-OF-CHOICE
    method->initialize_method(system,bath,io);
    allocate_result(io);

    // EXECUTE THE REDMAT CALCULATION WITH METHOD-OF-CHOICE

    //result_ = method->calculate_reduced_density_matrix(system,bath,io,pe);

    //result_ = pe.collect_result(result_);
    //if (pe.is_master()) write_result(io);

    return;
}

void MQDS::Absorption::allocate_result(MQDS::IO & io)
{
    int tdim = io.nstep()/io.dump();
    result_.resize(tdim+1);
    for (int idim=0; idim<tdim+1; ++idim)
    {
        result_[idim].resize(io.nstate(),io.nstate());
    }
    return;
}

void MQDS::Absorption::write_result(MQDS::IO &io)
{
    std::stringstream filename;
    std::ofstream output;

    for (int istate=0; istate<io.nstate(); ++istate)
    {
        for (int jstate=0; jstate<io.nstate(); ++jstate)
        {
            filename << io.method() << "." << istate+1 << "-" <<jstate+1;
            output.open(filename.str());

            for (int itime=0; itime<result_.size(); ++itime)
            {
                output << itime*io.dump()*io.runtime()/io.nstep()
                       << '\t' << result_[itime](istate,jstate).real()
                       << '\t' << result_[itime](istate,jstate).imag()
                       << '\n';
            }

            filename.str("");
            output.close();
        }
    }


    return;
}