//
// Created by Justin Provazza on 10/9/18.
//

#include "../../include/MQDS/universe.h"
#include <mpi.h>

// Constructor initializes MPI and determines how many processors and who I am
Universe::Universe()
{
    MPI_Init(nullptr, nullptr);
    numprocs = get_num_procs();
    mype = get_my_pe();
}

// Destructor finalizes MPI
Universe::~Universe()
{
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}

// Figure out how many processors are being used
int Universe::get_num_procs()
{
    int m_numprocs;
    MPI_Comm_size(MPI_COMM_WORLD, &m_numprocs);
    return m_numprocs;
}

// Figure out which processing element I am
int Universe::get_my_pe()
{
    int m_mype;
    MPI_Comm_rank(MPI_COMM_WORLD, &m_mype);
    return m_mype;
}

