//
// Created by Justin Provazza on 10/26/18.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "MQDS/random.h"
#include "MQDS/constants.h"


// Returns a double precision uniformly-distributed random
// number in the range [&min,&max)
void MQDS::Random::set_local_seed(int const &mype)
{
    std::srand(static_cast<unsigned int>((unsigned int) (5 * mype + 1 ) * std::time(nullptr) + 3 * mype));
}

double MQDS::Random::uniform_random_number(double const &min, double const &max)
{
    double m_uniform;
    m_uniform = min + (max - min) * rand() / (RAND_MAX);

    return m_uniform;
}

// Returns a double precision gaussian-distributed random
// number in centered about &center with variance &variance
double MQDS::Random::gaussian_random_number(double const &center, double const &variance) {
    double m_gauss;
    m_gauss = std::sqrt(-2.0 * std::log(MQDS::Random::uniform_random_number(0.0, 1.0)))
              * std::cos( 2.0 * MQDS::Constants::pi * MQDS::Random::uniform_random_number(0.0, 1.0));

    return m_gauss;
}
