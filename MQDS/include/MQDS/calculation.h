//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_CALCULATION_H
#define MQDS_CALCULATION_H


#include "MQDS/method.h"
#include "MQDS/io.h"
#include "MQDS/system.h"
#include "MQDS/bath.h"
#include "MQDS/universe.h"
#include "method.h"
#include <memory>
#include <map>
#include <vector>
#include <functional>
#include <Eigen/Dense>


namespace MQDS {
    class Calculation {
    public:
        Calculation() = default;

        virtual ~Calculation() = default;

        virtual void calculate
                (std::unique_ptr<Method> & method,
                 std::unique_ptr<System> & system,
                 std::unique_ptr<Bath> & bath,
                 MQDS::IO & io,
                 MQDS::Universe & pe)=0;

        virtual void report_type()= 0;

        std::vector<Eigen::MatrixXcd> result(){return result_;};

        virtual void allocate_result(MQDS::IO & io)=0;

        virtual void write_result(MQDS::IO & io)=0;
    private:

    protected:
        std::vector<Eigen::MatrixXcd> result_;
    };
};

#endif //MQDS_CALCULATION_H
