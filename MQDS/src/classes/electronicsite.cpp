//
// Created by Justin Provazza on 12/8/18.
//

#include "MQDS/electronicsite.h"
#include "MQDS/system.h"
#include "MQDS/io.h"
#include "MQDS/constants.h"

// GET THE INITIAL TRAJECTORY WEIGHT
std::complex<double> MQDS::ElectronicSite::get_initial_mapping_weight(const int &initstate, const int &initstatet)
{
    return 0.5*(position_map_[0](initstate) - MQDS::Constants::eye * momentum_map_[0](initstate))
            * (position_map_[1](initstatet) + MQDS::Constants::eye * momentum_map_[1](initstatet));
}