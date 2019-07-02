//
// Created by Justin Provazza on 10/9/18.
//
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <functional>
#include <vector>
#include "MQDS/method.h"

void MQDS::Method::allocate_redmat(MQDS::IO & io)
{
    int tdim = io.nstep()/io.dump();
    redmat_.resize(tdim+1);
    for (int idim=0; idim<tdim+1; ++idim)
    {
        redmat_[idim].resize(io.nstate(),io.nstate());
    }
    return;
}