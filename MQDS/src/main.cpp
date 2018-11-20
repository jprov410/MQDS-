#include <iostream>
#include "../include/MQDS/universe.h"
#include "../include/MQDS/input.h"
#include "../include/MQDS/units.h"
#include "../include/MQDS/random.h"
#include "../include/MQDS/constants.h"
#include "../include/MQDS/output.h"

using namespace MQDS;
int main()
{
    // Figure out who I am and provide pseudo-random number generator
    // with a processor-dependent seed
    Universe my_proc;
    Random::set_local_seed(my_proc.my_pe());

    // Gather input information
    Input in;

    if (my_proc.is_master()) Output::write_run_parameters();

    // Set precision for output
    std::cout.precision( 17 );

    //std::cout << in.temperature() << std::endl;

    return 0;
}