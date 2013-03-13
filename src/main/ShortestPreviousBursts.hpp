/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef SHORTEST_PREVIOUS_BURSTS_H
#define SHORTEST_PREVIOUS_BURSTS_H

#include "Algorithm.hpp"

class ShortestPreviousBursts : public Algorithm {
public:
    ShortestPreviousBursts(std::vector<ProcessControlBlock> rawData, int quantumTime);
    void run();
    
    std::vector<ProcessControlBlock> getFinalQueueOrder();
private:
    
};

#endif
