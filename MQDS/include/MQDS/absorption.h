//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_ABSORPTION_H
#define MQDS_ABSORPTION_H

#include "MQDS/calculation.h"
#include "MQDS/calculationfactory.h"
#include <memory>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

namespace MQDS {
    class Absorption : public Calculation {
    public:
        Absorption() = default;

        virtual ~Absorption() = default;

        virtual void report_type() override {
            std::cout << "Calculation: Absorption" << std::endl;
        };

        virtual void calculate
                (std::unique_ptr<Method> & method,
                 std::unique_ptr<System> & system,
                 std::unique_ptr<Bath> & bath,
                 MQDS::IO & io,
                 MQDS::Universe & pe) override;

        virtual void allocate_result(MQDS::IO & io) override;

        virtual void write_result(MQDS::IO & io) override;
    private:
    protected:
    };
    static bool absorption_registration =
            MQDS::CalculationFactory::Register("Absorption", []() -> std::unique_ptr<MQDS::Calculation>
            { return std::make_unique<MQDS::Absorption>(); });
};
#endif //MQDS_ABSORPTION_H
