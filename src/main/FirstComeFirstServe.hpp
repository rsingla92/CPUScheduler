/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef FIRST_COME_FIRST_SERVE_H
#define FIRST_COME_FIRST_SERVE_H

#include "Algorithm.hpp"
#include <iostream>

class FirstComeFirstServe : public Algorithm {
public:
    FirstComeFirstServe(std::vector<ProcessControlBlock> rawData);
    void run();

    std::vector<ProcessControlBlock> getFinalQueueOrder();
private:

};

#endif
