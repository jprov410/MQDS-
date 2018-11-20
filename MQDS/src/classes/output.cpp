//
// Created by Justin Provazza on 10/9/18.
//

#include "../../include/MQDS/output.h"
#include "../../include/MQDS/input.h"
#include "../../include/MQDS/universe.h"
#include <fstream>
#include <iostream>

namespace
{
    std::ofstream runlog("run.log");
}

void const MQDS::Output::write_run_parameters()
{
    {
        if (runlog.is_open())
        {
            //MQDS::Universe::is_master();
            std::cout << "made it here" << std::endl;
            //TODO write stuff to the runlog file

        }
    }
}