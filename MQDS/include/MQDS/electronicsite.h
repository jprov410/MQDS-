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
#include <complex>

namespace MQDS
{
    class ElectronicSite : public MQDS::System
    {
    public:
        ElectronicSite()= default;

        virtual ~ElectronicSite() = default;

        virtual void report_type() override {
            std::cout << "System Type: ElectronicSite" << std::endl;
        };

    private:
    protected:
        virtual std::complex<double> get_initial_mapping_weight(const int &initstate, const int &initstatet) override;
    };
    static bool electronicsite_registration =
            MQDS::SystemFactory::Register("ElectronicSite", []() -> std::unique_ptr<MQDS::System>
        { return std::make_unique<MQDS::ElectronicSite>();});
};
#endif //MQDS_SITE_ELECTRONIC_H
