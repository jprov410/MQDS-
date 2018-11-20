//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_INPUT_H
#define MQDS_INPUT_H
#include <vector>
#include <string>
namespace MQDS
{
    class Input;
}

class MQDS::Input
{
public:
    Input();
    //TODO make a function that outputs run parameter values

    int const & ntraj() const {return ntraj_;};
    int const & nstate() const {return nstate_;};
    int const & nstep() const {return nstep_;};
    int const & nlit() const {return nlit_;};
    int const & dump() const {return dump_;};
    int const & initstate() const {return initstate_;};
    int const & initstatet() const {return initstatet_;};

    std::string const & method() const {return method_;};
    std::string const & calculation() const {return calculation_;};
    std::string const & window_shape() const {return window_shape_;};
    std::string const & system_basis() const {return system_basis_;};

    double const & temperature() const {return temperature_;};

private:
    // FUNCTIONS
    void const read_runfile();
    void const set_defaults();
    void const assign_value(std::string const &key,
                            std::vector<std::string> const &tokens);

    // MAPS AND VECTORS OF STRINGS
    std::vector<std::string> static const runfile_keywords;

    // INTEGERS
    int nstate_, ntraj_, nstep_, nlit_, dump_, initstate_, initstatet_;

    // STRINGS
    std::string method_, calculation_, window_shape_;
    std::string system_basis_, bath_potential_;

    // DOUBLES
    double temperature_;

protected:
};


#endif //MQDS_INPUT_H
