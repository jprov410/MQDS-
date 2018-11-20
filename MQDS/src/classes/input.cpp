//
// Created by Justin Provazza on 10/9/18.
//

#include "../../include/MQDS/input.h"
#include "../../include/MQDS/units.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace
{
    std::ifstream runfile("run.in"); // input file with run parameters

    //TODO add more input file definitions

    std::string const comment_delim="//"; // delimiter to separate comments
    std::string const token_delim=" "; // delimiter to separate tokens

    // to deal with input files
    struct RunLine
    {
        std::string raw;
        std::string uncommented;
        std::vector<std::string> my_tokens;
        std::string my_keyword;

        // Remove all comments from current line
        void filter_comments()
        {
            uncommented = raw.substr(0,raw.find(comment_delim));
        };
        // Find all of the tokens un uncommented line
        void find_tokens()
        {
            size_t last = 0;
            size_t next = 0;

            while ((next = uncommented.find(token_delim,last))
                   != std::string::npos)
            {
            my_tokens.push_back(uncommented.substr(last, next - last));
                last = next + 1;
            }
            my_tokens.push_back(uncommented.substr(last));
        };
        // Check if one of the tokens is an element of keyword vector
        bool const contains_keyword( std::vector<std::string>const &keywords )
        {
            filter_comments();
            find_tokens();

            for ( auto &j : keywords )
            {
                if (my_tokens[0] == j){
                    my_keyword = my_tokens[0];
                    return true;
                }
            }
            return false;
        };


        //TODO need to figure out how to look for subsequent tokens to see if they can be expected type
    };

    std::string const assign_string( std::string const &val )
    {
            return val;
    };
    int const assign_integer( std::string const &val )
    {
            return stoi(val);
    };

    double const assign_double( std::string const &val )
    {
            return stod(val);
    };
}

//TODO create map to functions that set input values

MQDS::Input::Input()
{
    set_defaults();
    read_runfile();
}

void const MQDS::Input::read_runfile()
{
    RunLine line;

    while (std::getline(runfile,line.raw))
    {
        if (line.contains_keyword(runfile_keywords))
        {
            assign_value(line.my_keyword,line.my_tokens);
        }
    }
    runfile.close();
}

void const MQDS::Input::set_defaults()
{
    // INTEGER TYPE CALCULATION PARAMETERS
    ntraj_ = 100;
    nstate_ = 2;
    nstep_ = 100;
    nlit_ = 20;
    dump_ = 1;
    initstate_ = 1;
    initstatet_ = 1;

    // STRING TYPE CALCULATION PARAMETERS
    method_ = "pldm";
    calculation_ = "redmat";
    window_shape_= "square";
    system_basis_ = "site";
    bath_potential_ = "harmonic";

    // DOUBLE PRECISION TYPE CALCULATION PARAMETERS
    temperature_ = 77.0;
}

void const MQDS::Input::assign_value(std::string const &key,
                               std::vector<std::string> const &tokens)
{
    // ASSIGN STRING VALUES
    if (key == "method") method_ = assign_string(tokens[1]);
    if (key == "calculation") calculation_ = assign_string(tokens[1]);
    if (key == "window_shape") window_shape_ = assign_string(tokens[1]);
    if (key == "system_basis") system_basis_ = assign_string(tokens[1]);
    if (key == "bath_potential") bath_potential_ = assign_string(tokens[1]);

    // ASSIGN INTEGER VALUES
    if (key == "nstate") nstate_ = assign_integer(tokens[1]);
    if (key == "ntraj") ntraj_ = assign_integer(tokens[1]);
    if (key == "nstep") nstep_ = assign_integer(tokens[1]);
    if (key == "nlit") nlit_ = assign_integer(tokens[1]);
    if (key == "dump") dump_ = assign_integer(tokens[1]);
    if (key == "initstate") initstate_ = assign_integer(tokens[1]);
    if (key == "initstatet") initstatet_ = assign_integer(tokens[1]);

    // DOUBLE PRECISION VALUES
    if (key == "temperature") temperature_ = assign_double(tokens[1]);

}

// Vector of keywords for the run.in file
std::vector<std::string> const MQDS::Input::runfile_keywords =
        {
                // CHARACTER/STRING type parameters
                "method",         // dynamics method choice
                "calculation",    // type of calculation
                "window_shape",   // SQC windowing model
                "system_basis",   // site or exciton basis
                "bath_potential", // harmonic, multiple anharmonic types

                // INTEGER type parameters
                "nstate",    // number of system states
                "ntraj",     // number of trajectories for trajectory-based methods
                "nstep",     // number of time steps in simulation
                "nlit",      // number of little steps per big step if need finer
                // integration grid
                "dump",      // number of steps per observation
                "initstate", // initial state for fwd wavefunction
                "initstatet",// initial state for bkwd wavefunction

                // DOUBLE PRECISION type parameters
                "temperature", // temperature of simulation in Kelvin
        };


