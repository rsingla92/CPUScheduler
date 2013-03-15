/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef FACTORY_H
#define FACTORY_H

#include "Algorithm.hpp"
#include "TimeSlicePriority.hpp"
#include "FirstComeFirstServe.hpp"
#include "InstantPriority.hpp"
#include "NonPreemptivePriority.hpp"
#include "PreShortestJobFirst.hpp"
#include "ShortestPreviousBursts.hpp"
#include "NonPreemptiveShortestJobFirst.hpp"
#include <limits>

class Factory
{
public:
    static Algorithm* factory_makeAlgorithm(std::string algorithmType, std::vector<ProcessControlBlock> rawData, int timeQuantum);
};

#endif
