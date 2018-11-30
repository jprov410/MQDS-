#include <iostream>
#include "MQDS/universe.h"
#include "MQDS/io.h"
#include "MQDS/units.h"
#include "MQDS/random.h"
#include "MQDS/constants.h"



using namespace MQDS;
int main()
{
    // Figure out who I am and provide pseudo-random number generator
    // with a processor-dependent seed
    Universe my_proc;
    Random::set_local_seed(my_proc.my_pe());
    // Gather input information
    IO io;

    if (my_proc.is_master()) io.write_run_parameters();

    // Set precision for output
    std::cout.precision( 17 );

    //std::cout << in.temperature() << std::endl;

    return 0;
}