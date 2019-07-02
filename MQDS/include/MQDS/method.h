//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_METHOD_H
#define MQDS_METHOD_H

#include<iostream>
#include <string>
#include "MQDS/io.h"
#include "MQDS/system.h"
#include "MQDS/bath.h"
#include "MQDS/universe.h"
#include <memory>
#include <map>
#include <vector>
#include <functional>
#include <Eigen/Dense>

namespace MQDS
{
    class Method
    {
    public:
        Method() = default;

        virtual ~Method() = default;

        virtual void report_type()= 0;

        virtual void initialize_method(std::unique_ptr<System> & system,
                                       std::unique_ptr<Bath> & bath,
                                       MQDS::IO & io)=0;

        virtual std::vector<Eigen::MatrixXcd> calculate_reduced_density_matrix(std::unique_ptr<System> & system,
                                                      std::unique_ptr<Bath> & bath,
                                                      MQDS::IO & io,
                                                      MQDS::Universe & pe)=0;


        virtual Eigen::MatrixXcd redmat_function(std::unique_ptr<System> & system)=0;


        virtual void propagate(std::unique_ptr<System> & system,
                               std::unique_ptr<Bath> & bath,
                               const double & dt,
                               const int & nlit)=0;

        virtual std::vector<Eigen::MatrixXd> what_bath_feels(std::unique_ptr<System> & system,
                                                             std::unique_ptr<Bath> & bath)=0;

        virtual Eigen::MatrixXd what_system_feels(const int &ibath,
                                                  std::unique_ptr<System> & system,
                                                  std::unique_ptr<Bath> & bath)=0;

    private:

    protected:
        std::vector<Eigen::MatrixXcd> redmat_;
        virtual void allocate_redmat(MQDS::IO & io);
    };
};

#endif //MQDS_METHOD_H
