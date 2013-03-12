/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "Algorithm.hpp"
#include <iostream>

class RoundRobin : public Algorithm {
public:
    RoundRobin(std::vector<ProcessControlBlock> rawData, int quantumTime);
    void run();
    
    std::vector<ProcessControlBlock> getFinalQueueOrder();
private:
    
};

#endif
