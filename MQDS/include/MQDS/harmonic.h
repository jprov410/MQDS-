//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_HARMONIC_H
#define MQDS_HARMONIC_H

#include "MQDS/bath.h"
#include "MQDS/bathfactory.h"
#include <memory>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

namespace MQDS
{
    class Harmonic;
}

class MQDS::Harmonic : virtual public MQDS::Bath
{
public:
    Harmonic() = default;
    virtual ~Harmonic() = default;

    virtual void report_type() override{
        std::cout << "Bath Potential Type: Harmonic" << std::endl;
    };
private:
    static bool s_registered;
protected:
};

bool MQDS::Harmonic::s_registered =
        MQDS::BathFactory::Register("Harmonic", []() -> std::unique_ptr<MQDS::Bath>
        { return std::make_unique<MQDS::Harmonic>();});

#endif //MQDS_HARMONIC_H
