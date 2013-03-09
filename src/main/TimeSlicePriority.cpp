/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "TimeSlicePriority.hpp"


TimeSlicePriority::TimeSlicePriority(std::vector<ProcessControlBlock> inputRawData, int quantumTime) 
	: Algorithm(inputRawData, quantumTime)
{
}


TimeSlicePriority::~TimeSlicePriority(void)
{
}
