/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef NONPREEMPTIVE_PRIORITY_H
#define NONPREEMPTIVE_PRIORITY_H

#include "Algorithm.hpp"

class NonPreemptivePriority : public Algorithm {
public:
    NonPreemptivePriority(std::vector<ProcessControlBlock> rawData, int quantumTime, bool aging);
    void run();
    
};

#endif
