//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_SYSTEM_H
#define MQDS_SYSTEM_H

#include <iostream>
#include <string>
#include "MQDS/io.h"
#include <memory>
#include <map>
#include <vector>
#include <functional>
#include <Eigen/Dense>

namespace MQDS
{
    class System
    {
    public:
        System()=default;

        virtual ~System() = default;

        virtual void report_type()= 0;

        virtual void read_hamiltonian(int const &nstate);

        virtual void read_dipole_matrix(int const &nstate);

        virtual Eigen::MatrixXd & hamiltonian(){return hamiltonian_;};

        virtual std::complex<double> & initial_trajectory_weight(){return initial_trajectory_weight_;};

        virtual std::vector<Eigen::VectorXd> & position_map(){return position_map_;};

        virtual std::vector<Eigen::VectorXd> & momentum_map(){return momentum_map_;};

        virtual void initialize_mapping_variables(const int &ncopies, const int &nstate);

        virtual void gaussian_mapping_initial_conditions(const double &mean,
                                                         const double &sigma);

        virtual void assign_initial_trajectory_weight(const std::complex<double> & initial_weight);

        virtual void advance_mapping_variables(const int &system_copy,
                                                const Eigen::MatrixXd &what_system_feels,
                                                const double &total_timestep,
                                                const int &nstep);
        //virtual void
    protected:
        std::complex<double> initial_trajectory_weight_;
        Eigen::MatrixXd hamiltonian_;
        std::vector<Eigen::VectorXd> position_map_,momentum_map_;
        std::vector<std::vector<Eigen::Vector3d>> dipole_components_;
    private:
    };
};


#endif //MQDS_SYSTEM_H
