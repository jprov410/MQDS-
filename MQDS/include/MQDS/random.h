//
// Created by Justin Provazza on 10/26/18.
//

#ifndef MQDS_RANDOM_H
#define MQDS_RANDOM_H


namespace MQDS::Random
{
    // Sets the psuedo-random number generator seed
    // using the processing element number as an argument
    void set_local_seed( int const &mpye);

    // Returns a double precision uniformly-distributed
    // pseudo-random number in the range [&min,&max)
    double uniform_random_number( double const &min, double const &max);

    // Returns a double precision gaussian-distributed pseudo-random
    // number in centered about &center with variance &variance
    double gaussian_random_number( double const &center, double const &variance);

};


#endif //MQDS_RANDOM_H
