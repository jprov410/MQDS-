//
// Created by Justin Provazza on 10/9/18.
//

#include "../../include/MQDS/universe.h"
#include <mpi.h>


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
}