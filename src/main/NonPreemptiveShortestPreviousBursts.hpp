/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef NON_PREEMPTIVE_SHORTEST_PREVIOUS_BURSTS_H
#define NON_PREEMPTIVE_SHORTEST_PREVIOUS_BURSTS_H

#include "Algorithm.hpp"

class NonPreemptiveShortestPreviousBursts : public Algorithm {
public:
    NonPreemptiveShortestPreviousBursts(std::vector<ProcessControlBlock> rawData, bool aging, float alpha);
    void run();
    
};

#endif
