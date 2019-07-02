//
// Created by Justin Provazza on 10/9/18.
//

#include "MQDS/bath.h"

void MQDS::Bath::initialize_phase_space
        (const int &ncopies, const int &nbath, const int &nosc)
{
    //RESIZE PHASE SPACE VECTORS FOR EACH BATH
    position_.resize(ncopies);
    momentum_.resize(ncopies);
    force_.resize(ncopies);
    for (int icopy=0; icopy<ncopies ; ++icopy)
    {
        position_[icopy].resize(nbath);
        momentum_[icopy].resize(nbath);
        force_[icopy].resize(nbath);
    }
    for (int icopy=0; icopy<ncopies ; ++icopy)
    {
        for (int ibath = 0; ibath < nbath; ++ibath)
        {
            position_[icopy][ibath].resize(nosc);
            momentum_[icopy][ibath].resize(nosc);
            force_[icopy][ibath].resize(nosc);
        }
    }
}

void MQDS::Bath::advance_position(const double &timestep)
{
    for (int icopy=0; icopy < position_.size(); ++icopy)
    {
        for (int ibath=0; ibath < position_[0].size(); ++ibath)
        {
            for(int imode=0; imode<position_[0][0].size(); ++imode)
            {
                position_[icopy][ibath](imode) = position_[icopy][ibath](imode)
                                                 + momentum_[icopy][ibath](imode) * timestep;
            }
        }
    }
    return;
}

void MQDS::Bath::advance_momentum
        (const std::vector<Eigen::MatrixXd> & method_specific_sb, const double &timestep)
{
    compute_force(method_specific_sb);
    for (int icopy=0; icopy < momentum_.size(); ++icopy)
    {
        for (int ibath=0; ibath < momentum_[0].size(); ++ibath)
        {
            for(int imode=0; imode<momentum_[0][0].size(); ++imode)
            {
                momentum_[icopy][ibath](imode) = momentum_[icopy][ibath](imode)
                                                 + force_[icopy][ibath](imode) * timestep;
            }
        }
    }
    return;
}