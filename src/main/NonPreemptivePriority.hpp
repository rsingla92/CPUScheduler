/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef NONPREEMPTIVE_PRIORITY_H
#define NONPREEMPTIVE_PRIORITY_H

#include "Algorithm.hpp"
#include <iostream>

class NonPreemptivePriority : public Algorithm {
public:
    NonPreemptivePriority(std::vector<ProcessControlBlock> rawData, int quantumTime);
    void run();
    
    std::vector<ProcessControlBlock> getFinalQueueOrder();
private:
    
};

#endif
