//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_REDMAT_H
#define MQDS_REDMAT_H

#include "MQDS/calculation.h"
#include "MQDS/calculationfactory.h"
#include <memory>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

namespace MQDS
{
    class RedMat;
}

class MQDS::RedMat : public MQDS::Calculation
{
public:
    RedMat() = default;
    virtual ~RedMat() = default;

    virtual void report_type() override {
        std::cout << "Calculation: RedMat" << std::endl;
    };
private:
    static bool s_registered;
protected:
};

bool MQDS::RedMat::s_registered =
        MQDS::CalculationFactory::Register("RedMat", []() -> std::unique_ptr<MQDS::Calculation>
        { return std::make_unique<MQDS::RedMat>();});

#endif //MQDS_REDMAT_H
