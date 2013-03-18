/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef IMPATIENT_PRIORITY_H
#define IMPATIENT_PRIORITY_H

#include "Algorithm.hpp"

class ImpatientPriority: public Algorithm {
public:
    ImpatientPriority(std::vector<ProcessControlBlock> rawData, int quantumTime, bool aging);
    void run();
};

#endif
