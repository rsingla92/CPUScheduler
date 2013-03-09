/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#ifndef TIME_SLICE_PRIORITY_H
#define TIME_SLICE_PRIORITY_H

#include "Algorithm.hpp"

class TimeSlicePriority :
	public Algorithm
{
public:
	TimeSlicePriority(std::vector<ProcessControlBlock> inputRawData, int quantumTime);
	~TimeSlicePriority(void);


};

#endif

