#include <iostream>
#include "../include/MQDS/universe.h"
#include "../include/MQDS/input.h"
#include "../include/MQDS/units.h"
#include "../include/MQDS/random.h"
#include "../include/MQDS/constants.h"

int main()
{
    // Figure out who I am and provide pseudo-random number generator
    // with a processor-dependent seed
    Universe process;
    Random::set_local_seed(process.mype);
    std::cout.precision( 17 );

    //std::cout << Units::conversion(
//            Units::wavenumber, Units::atomic_energy ) << std::endl;

    //std::cout << process.mype << "    " << Random::uniform_random_number(0.0,1.0) << std::endl;

    {
        std::cout << Units::conversion(Units::wavenumber,Units::atomic_energy) << std::endl;
    }
    return 0;

}

