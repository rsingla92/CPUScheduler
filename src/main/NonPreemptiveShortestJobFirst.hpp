/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef NON_PREEMPTIVE_SHORTEST_JOB_FIRST_H
#define NON_PREEMPTIVE_SHORTEST_JOB_FIRST_H

#include "Algorithm.hpp"

class NonPreShortestJobFirst : public Algorithm {
public:
    NonPreShortestJobFirst(std::vector<ProcessControlBlock> rawData, int quantumTime);
    void run();
    
    std::vector<ProcessControlBlock> getFinalQueueOrder();
private:
    
};

#endif
