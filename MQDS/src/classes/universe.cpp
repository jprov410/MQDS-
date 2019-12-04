//
// Created by Justin Provazza on 10/9/18.
//

#include "MQDS/universe.h"
#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <complex>


// Constructor initializes MPI and determines how many processors and who I am
MQDS::Universe::Universe()
{
    MPI_Init(nullptr, nullptr);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs_);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe_);
}

// Destructor finalizes MPI
MQDS::Universe::~Universe()
{
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}

// Figure out how many processors are being used
int const MQDS::Universe::num_procs()
{
    return num_procs_;
}

// Figure out which processing element I am
int const MQDS::Universe::my_pe()
{
    return my_pe_;
}

bool const MQDS::Universe::is_master()
{
    return (my_pe_ == master_pe_);
}

void MQDS::Universe::broadcast()
{
    //TODO need to figure out how to broadcast arbitrary data type
    MPI_Barrier(MPI_COMM_WORLD);
    //MPI_Bcast();
    return;
}

std::vector<Eigen::MatrixXcd> MQDS::Universe::collect_result(std::vector<Eigen::MatrixXcd> &result)
{
    std::vector<Eigen::MatrixXcd> avg;
    avg.resize(result.size());
    MPI_Barrier(MPI_COMM_WORLD);
    std::complex<double> nproc(num_procs_,0.0);

    for (int itime=0; itime<result.size(); ++itime)
    {
        avg[itime].resize(std::sqrt(result[itime].size()),std::sqrt(result[itime].size()));
        MPI_Reduce(result[itime].data(),avg[itime].data(),result[itime].size(),
                   MPI_COMPLEX16,MPI_SUM,master_pe_,MPI_COMM_WORLD);
    }

    for (int itime=0; itime<result.size(); ++itime)
    {
        for (int istate=0; istate<std::sqrt(result[itime].size()); ++istate)
        {
            for (int jstate=0; jstate<std::sqrt(result[itime].size()); ++jstate)
            {
                avg[itime](istate,jstate) = avg[itime](istate,jstate)/nproc;
            }
        }
    }
    return avg;
}

