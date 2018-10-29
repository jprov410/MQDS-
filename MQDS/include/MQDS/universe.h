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
    int numprocs;
    int mype;
    int masterpe = 0;
private:
    int get_num_procs();
    int get_my_pe();
protected:
};


#endif //MQDS_UNIVERSE_H
