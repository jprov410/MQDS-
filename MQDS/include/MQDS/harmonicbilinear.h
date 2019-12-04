//
// Created by Justin Provazza on 12/8/18.
//

#ifndef MQDS_HARMONIC_BILINEAR_H
#define MQDS_HARMONIC_BILINEAR_H

#include "MQDS/bath.h"
#include "MQDS/bathfactory.h"
#include "MQDS/io.h"
#include <memory>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

namespace MQDS
{
    class HarmonicBilinear : public Bath
    {
    public:
        HarmonicBilinear();

        virtual ~HarmonicBilinear() = default;

        virtual void report_type() override {
            std::cerr << "Bath Potential Type: HarmonicBilinear" << std::endl;
        };

        virtual void read_input(const int &nbath,const int &nosc,const int &nstate) override;

        virtual void bare_boltzmann_wigner_initial_conditions(const double &beta) override;

        virtual void compute_force
                (const std::vector<Eigen::MatrixXd> & method_specific_sb) override;

        virtual double sb_portion_of_hamiltonian(const int & bathcopy,
                                                 const int & istate,
                                                 const int & jstate) override;
    private:
    protected:
    };
    static bool harmonicbilinear_registration= MQDS::BathFactory::Register
            ("HarmonicBilinear", []() -> std::unique_ptr<MQDS::Bath>
            { return std::make_unique<MQDS::HarmonicBilinear>(); });;
};


#endif //MQDS_HARMONIC_BILINEAR_H
