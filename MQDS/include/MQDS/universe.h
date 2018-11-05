//
// Created by Justin Provazza on 10/9/18.
//

#ifndef MQDS_UNIVERSE_H
#define MQDS_UNIVERSE_H


class Universe
{
public:
    Universe();
    ~Universe();
    int const get_num_procs();
    int const get_my_pe();
    bool const is_master();
private:
    int numprocs;
    int mype;
    int const masterpe = 0;
protected:
};


#endif //MQDS_UNIVERSE_H
