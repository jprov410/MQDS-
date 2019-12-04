//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_PLDM_H
#define MQDS_PLDM_H

#include "MQDS/method.h"
#include "MQDS/methodfactory.h"
#include "MQDS/universe.h"
#include <memory>
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <complex>
#include <Eigen/Dense>

namespace MQDS
{
    class PLDM : public Method
    {
    public:
        PLDM() = default;

        virtual ~PLDM() = default;

        virtual void report_type() override {
            std::cout << "Method: PLDM" << std::endl;
        };


        virtual void initialize_method(std::unique_ptr<System> & system,
                                       std::unique_ptr<Bath> & bath,
                                       MQDS::IO & io) override;

        virtual std::vector<Eigen::MatrixXcd> calculate_reduced_density_matrix(std::unique_ptr<System> & system,
                                                      std::unique_ptr<Bath> & bath,
                                                      MQDS::IO & io,
                                                      MQDS::Universe & pe) override;

        virtual void propagate(std::unique_ptr<System> & system,
                               std::unique_ptr<Bath> & bath,
                               const double & dt,
                               const int & nlit) override;

        virtual Eigen::MatrixXcd
        redmat_function(std::unique_ptr<System> & system) override;

        virtual std::vector<Eigen::MatrixXd> what_bath_feels(std::unique_ptr<System> & system,
                                                             std::unique_ptr<Bath> & bath) override;

        virtual Eigen::MatrixXd what_system_feels(const int &ibath,
                                                  std::unique_ptr<System> & system,
                                                  std::unique_ptr<Bath> & bath) override;

        virtual std::complex<double> initial_trajectory_weight(std::unique_ptr<System> & system,
                                                               const int & initstate,
                                                               const int & initstatet) override;
    private:
    protected:
    };
static bool pldm_registration =
        MQDS::MethodFactory::Register("PLDM", []() -> std::unique_ptr<MQDS::Method>
        { return std::make_unique<MQDS::PLDM>();});
};
#endif //MQDS_PLDM_H
