/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef SHORTEST_JOB_FIRST_H
#define SHORTEST_JOB_FIRST_H

#include "Algorithm.hpp"

class PreShortestJobFirst : public Algorithm {
public:
    PreShortestJobFirst(std::vector<ProcessControlBlock> rawData, int quantumTime);
    void run();
    
    std::vector<ProcessControlBlock> getFinalQueueOrder();
private:
    
};

#endif