//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_BATH_H
#define MQDS_BATH_H

#include <iostream>
#include <string>
#include "MQDS/io.h"
#include <memory>
#include <map>
#include <vector>
#include <functional>
namespace MQDS
{
    class Bath
    {
    public:
        Bath() = default;

        virtual ~Bath() = default;

        virtual void report_type()= 0;

    private:

    protected:
    };
};
#endif //MQDS_BATH_H
