//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_PLDM_H
#define MQDS_PLDM_H

#include "MQDS/method.h"
#include "MQDS/methodfactory.h"
#include <memory>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

namespace MQDS
{
    class PLDM : public MQDS::Method
    {
    public:
        PLDM() = default;

        virtual ~PLDM() = default;

        virtual void report_type() override {
            std::cout << "Method: PLDM" << std::endl;
        };

        virtual void calculate
                (std::unique_ptr<Calculation> & calculation,
                 std::unique_ptr<System> & system,
                 std::unique_ptr<Bath> & bath,
                 MQDS::IO & my_io) override;

    private:
    protected:
    };
static bool pldm_registration =
        MQDS::MethodFactory::Register("PLDM", []() -> std::unique_ptr<MQDS::Method>
        { return std::make_unique<MQDS::PLDM>();});
};
#endif //MQDS_PLDM_H
