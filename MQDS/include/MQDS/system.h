//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_SYSTEM_H
#define MQDS_SYSTEM_H

#include <iostream>
#include <string>
#include "MQDS/io.h"
#include <memory>
#include <map>
#include <vector>
#include <functional>

namespace MQDS
{
    class System
    {
    public:
        System() = default;

        virtual ~System() = default;

        virtual void report_type()= 0;

    private:

    protected:
    };
};


#endif //MQDS_SYSTEM_H
