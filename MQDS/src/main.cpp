#include <iostream>
#include <memory>
#include <functional>
#include <map>
#include <vector>
#include <cassert>
#include "MQDS/universe.h"
#include "MQDS/io.h"
#include "MQDS/units.h"
#include "MQDS/random.h"
#include "MQDS/constants.h"
#include "MQDS/system.h"
#include "MQDS/electronicsite.h"
#include "MQDS/systemfactory.h"



using namespace MQDS;
int main()
{
    std::cout.precision( 17 ); // Set precision for cout
    Universe my_proc; // Initiate MPI
    Random::set_local_seed(my_proc.my_pe()); // Set local seed
    IO io; // Gather input information
    if (my_proc.is_master()) io.write_run_parameters(); // start runlog

    auto system = SystemFactory::Create(io);
    if(static_cast<bool>(system)) {
        system->report_type();
    }
    else {
        std::cerr << "Did not initialize properly "<< std::endl;
    }
    return 0;
}