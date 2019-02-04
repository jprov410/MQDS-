//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_BATH_H
#define MQDS_BATH_H

#include <iostream>
#include <string>
#include "MQDS/io.h"
#include <memory>
#include <map>
#include <vector>
#include <functional>
namespace MQDS
{
    class Bath
    {
    public:
        Bath() = default;

        virtual ~Bath() = default;

        virtual void report_type()=0;

        virtual std::vector<std::vector<double>> const initial_conditions
                (const int &nbath, const int &nosc)=0;

        virtual void read_spectral_density(const int &nbath,const int &nosc,const int &nstate){};

        virtual void const propagate_half_step(){};

        virtual void const propagate_full_step(){};

    protected:
        // Frequencies, Force Constants, Positions, Momenta
        std::vector<std::vector<double>> frequency_, coupling_, position_, momentum_;
        // Matrix that controls which elements of system Hamiltonian contain SB coupling
        // This matrix contains values that scale the Force constants
        // (value squared controls reorg energy scaling)
        std::vector<std::vector<std::vector<double>>> sys_bath_coupling_;
    private:
    };
};
#endif //MQDS_BATH_H
