//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_UNIVERSE_H
#define MQDS_UNIVERSE_H

#include <Eigen/Dense>

namespace MQDS
{
    class Universe
    {
    public:
        Universe();

        ~Universe();

        int const num_procs();

        int const my_pe();

        bool const is_master();

        void broadcast();

        std::vector<Eigen::MatrixXcd> collect_result(std::vector<Eigen::MatrixXcd> & result);
    private:
        int num_procs_;
        int my_pe_;
        int const master_pe_ = 0;
    protected:
    };
};

#endif //MQDS_UNIVERSE_H
