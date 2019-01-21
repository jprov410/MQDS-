//
// Created by Justin Provazza on 12/8/18.
//

#include "MQDS/harmonicbilinear.h"
#include "MQDS/bath.h"
#include "MQDS/io.h"
#include <iostream>

void MQDS::HarmonicBilinear::init(IO & my_io)
{
    read_spectral_density(my_io);
    return;
}

void const MQDS::HarmonicBilinear::read_spectral_density(MQDS::IO &my_io)
{
    return;
}
