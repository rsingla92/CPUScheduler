/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef FACTORY_H
#define FACTORY_H

#include "Algorithm.hpp"
#include "PatientPriority.hpp"
#include "FirstComeFirstServe.hpp"
#include "ImpatientPriority.hpp"
#include "NonPreemptivePriority.hpp"
#include "PreemptiveShortestJobFirst.hpp"
#include "NonPreemptiveShortestPreviousBursts.hpp"
#include "PreemptiveShortestPreviousBursts.hpp"
#include "NonPreemptiveShortestJobFirst.hpp"
#include <limits>

class Factory
{
public:
    static Algorithm* factory_makeAlgorithm(std::string algorithmType, std::vector<ProcessControlBlock> rawData, int timeQuantum, 
		bool aging=false, float alpha = 1.0);
};

#endif
