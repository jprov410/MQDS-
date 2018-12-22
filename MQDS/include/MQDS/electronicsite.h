//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_SITE_ELECTRONIC_H
#define MQDS_SITE_ELECTRONIC_H

#include "MQDS/system.h"
#include "MQDS/systemfactory.h"
#include <memory>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

namespace MQDS
{
    class ElectronicSite;
}

class MQDS::ElectronicSite : virtual public MQDS::System
{
public:
    ElectronicSite() = default;
    virtual ~ElectronicSite() = default;

    virtual void report_type() override{
        std::cout << "Type: ElectronicSite" << std::endl;
    };
private:
    static bool s_registered;
protected:
};

bool MQDS::ElectronicSite::s_registered =
        MQDS::SystemFactory::Register("ElectronicSite", []() -> std::unique_ptr<MQDS::System>
        { return std::make_unique<MQDS::ElectronicSite>();});

#endif //MQDS_SITE_ELECTRONIC_H
