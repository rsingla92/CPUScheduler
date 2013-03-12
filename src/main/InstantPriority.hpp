/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef INSTANT_PRIORITY_H
#define INSTANT_PRIORITY_H

#include "Algorithm.hpp"
#include <iostream>

class InstantPriority : public Algorithm {
public:
    InstantPriority(std::vector<ProcessControlBlock> rawData, int quantumTime);
    void run();
    
    std::vector<ProcessControlBlock> getFinalQueueOrder();
private:
    
};

#endif
