/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef NON_PREEMPTIVE_SHORTEST_JOB_FIRST_H
#define NON_PREEMPTIVE_SHORTEST_JOB_FIRST_H

#include "Algorithm.hpp"

class NonPreemptiveShortestJobFirst : public Algorithm {
public:
    NonPreemptiveShortestJobFirst(std::vector<ProcessControlBlock> rawData);
    void run();
    
    std::vector<ProcessControlBlock> getFinalQueueOrder();
private:
    
};

#endif
