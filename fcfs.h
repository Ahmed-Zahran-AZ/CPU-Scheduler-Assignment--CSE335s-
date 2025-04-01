#ifndef FCFS_H
#define FCFS_H
#include "processqueue.h"

class FCFS
{
public:
    FCFS();
    void sort(ProcessQueue& queue);
    void calculateTimes(ProcessQueue& queue);
};

#endif // FCFS_H
