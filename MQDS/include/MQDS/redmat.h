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

namespace MQDS {
    class RedMat : public Calculation {
    public:
        RedMat() = default;

        virtual ~RedMat() = default;

        virtual void report_type() override {
            std::cout << "Calculation: RedMat" << std::endl;
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
    static bool redmat_registration =
            MQDS::CalculationFactory::Register("RedMat", []() -> std::unique_ptr<MQDS::Calculation>
            { return std::make_unique<MQDS::RedMat>(); });
};
#endif //MQDS_REDMAT_H
