//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_HARMONIC_BILINEAR_H
#define MQDS_HARMONIC_BILINEAR_H

#include "MQDS/bath.h"
#include "MQDS/bathfactory.h"
#include "MQDS/io.h"
#include <memory>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

namespace MQDS
{
    class HarmonicBilinear : public Bath
    {
    public:
        HarmonicBilinear() = default;

        virtual ~HarmonicBilinear() = default;

        virtual void report_type() override {
            std::cout << "Bath Potential Type: HarmonicBilinear" << std::endl;
        };

        virtual void init(IO & my_io) override ;

    private:
        void const read_spectral_density(IO & my_io);
    protected:
    };
    static bool harmonicbilinear_registration= MQDS::BathFactory::Register("HarmonicBilinear", []() -> std::unique_ptr<MQDS::Bath>
    { return std::make_unique<MQDS::HarmonicBilinear>(); });;
};


#endif //MQDS_HARMONIC_BILINEAR_H
