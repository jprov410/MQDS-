//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_METHOD_H
#define MQDS_METHOD_H

#include <iostream>
#include <string>
#include "MQDS/io.h"
#include <memory>
#include <map>
#include <vector>
#include <functional>

namespace MQDS
{
    class Method
    {
    public:
        Method() = default;

        virtual ~Method() = default;

        virtual void report_type()= 0;

    private:

    protected:
    };
};

#endif //MQDS_METHOD_H
