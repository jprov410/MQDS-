//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_CALCULATION_H
#define MQDS_CALCULATION_H

#include <iostream>
#include <string>
#include "MQDS/io.h"
#include <memory>
#include <map>
#include <vector>
#include <functional>


namespace MQDS
{
    class Calculation
    {
    public:
        Calculation() = default;

        virtual ~Calculation() = default;

        virtual void report_type()= 0;

    private:

    protected:
    };
};

#endif //MQDS_CALCULATION_H
