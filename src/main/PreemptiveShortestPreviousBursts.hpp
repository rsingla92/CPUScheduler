/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef PREEMPTIVE_SHORTEST_PREVIOUS_BURSTS_H
#define PREEMPTIVE_SHORTEST_PREVIOUS_BURSTS_H

#include "Algorithm.hpp"

class PreemptiveShortestPreviousBursts : public Algorithm {
public:
    PreemptiveShortestPreviousBursts(std::vector<ProcessControlBlock> rawData, int quantumTime);
    void run();
    
    std::vector<ProcessControlBlock> getFinalQueueOrder();
private:
    
};

#endif
