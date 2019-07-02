//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_BATH_H
#define MQDS_BATH_H

#include <iostream>
#include <string>
#include "MQDS/io.h"
#include "MQDS/system.h"
#include <memory>
#include <map>
#include <vector>
#include <functional>
#include <Eigen/Dense>

namespace MQDS
{
    class Bath
    {
    public:
        Bath() = default;
        virtual ~Bath() = default;


        std::vector<std::vector<Eigen::VectorXd>> position(){return position_;};

        std::vector<std::vector<Eigen::VectorXd>> momentum(){return momentum_;};

        virtual std::vector<std::vector<Eigen::VectorXd>> force(){return force_;};

        virtual void report_type()=0;

        virtual void initialize_phase_space
                (const int &ncopies,const int &nbath, const int &nosc);

        virtual void read_input(const int &nbath,const int &nosc,const int &nstate){};

        virtual void get_initial_conditions(const double &beta){};

        virtual void advance_position(const double &timestep);

        virtual void advance_momentum(const std::vector<Eigen::MatrixXd> & method_specific_sb,
                                      const double &timestep);

        virtual void compute_force(const std::vector<Eigen::MatrixXd> &method_specific_sb)=0;

        virtual double sb_portion_of_hamiltonian(const int &bathcopy,
                                                 const int &istate,
                                                 const int &jstate)=0;
    protected:
        // Positions, Momenta
        std::vector<std::vector<Eigen::VectorXd>> position_, momentum_;
        std::vector<std::vector<Eigen::VectorXd>> force_;
        // Frequencies, Force Constants
        std::vector<Eigen::VectorXd> frequency_, coupling_;

        // Matrix that controls which elements of system Hamiltonian contain SB coupling
        // This matrix contains values that scale the Force constants
        // (value squared controls reorg energy scaling)
        std::vector<Eigen::MatrixXd> sys_bath_coupling_;
    private:
    };
};
#endif //MQDS_BATH_H
