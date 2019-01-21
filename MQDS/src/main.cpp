//External Libraries
#include <iostream>
#include <memory>
#include <functional>
#include <map>
#include <vector>
#include <cassert>
//General
#include "MQDS/universe.h"
#include "MQDS/io.h"
#include "MQDS/units.h"
#include "MQDS/random.h"
#include "MQDS/constants.h"
//SuperClasses
#include "MQDS/bath.h"
#include "MQDS/system.h"
#include "MQDS/method.h"
#include "MQDS/calculation.h"
//Factories
#include "MQDS/systemfactory.h"
#include "MQDS/bathfactory.h"
#include "MQDS/methodfactory.h"
#include "MQDS/calculationfactory.h"
//SubClasses
#include "MQDS/electronicsite.h"
#include "MQDS/harmonicbilinear.h"
#include "MQDS/pldm.h"
#include "MQDS/redmat.h"
using namespace MQDS;
int main()
{
    std::cout.precision( 17 ); // Set precision for cout
    Universe pe; // Initiate MPI. (Processing Element) = pe
    Random::set_local_seed(pe.my_pe()); // Set local seed

    IO io; // Gather input information

    if (pe.is_master()) io.write_run_parameters(); // start runlog

    auto system = SystemFactory::Create(io);
    if(static_cast<bool>(system)) {
        system->report_type();
    }
    else {
        std::cerr << "Did not initialize System properly "<< std::endl;
    }

    auto bath = BathFactory::Create(io);
    if(static_cast<bool>(bath)) {
        bath->report_type();
    }
    else {
        std::cerr << "Did not initialize Bath properly "<< std::endl;
    }

    auto method = MethodFactory::Create(io);
    if(static_cast<bool>(method)) {
        method->report_type();
    }
    else {
        std::cerr << "Did not initialize Method properly "<< std::endl;
    }

    auto calculation = CalculationFactory::Create(io);
    if(static_cast<bool>(calculation)) {
        calculation->report_type();
    }
    else {
        std::cerr << "Did not initialize Calculation properly "<< std::endl;
    }

    bath->init(io);
    return 0;
}