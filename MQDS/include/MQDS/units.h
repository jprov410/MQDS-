//
// Created by Justin Provazza on 10/21/18.
//

#ifndef MQDS_UNITS_H
#define MQDS_UNITS_H
#include <map>
namespace Units
{
    // Function that returns unit conversion factor for transforming from
    // units of &from to units of &to
    double conversion(std::string const &from_units, std::string const &to_units);

    // Library of units supported by conversion function
    extern std::string const atomic_energy;
    extern std::string const atomic_angular_frequency;
    extern std::string const wavenumber;
    extern std::string const seconds;
    extern std::string const hertz;

    // Map that takes input strings and returns float unit conversion factor
    //extern std::map<std::pair<std::string, std::string >, double> const conversion_map;
};

#endif //MQDS_UNITS_H
