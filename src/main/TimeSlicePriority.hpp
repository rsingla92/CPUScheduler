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
	~TimeSlicePriority( void );

	void run();
	std::vector<ProcessControlBlock> getFinalQueueOrder();

private: 
	/* Constants used by the class */
	static const int NO_WAITING_PROCESSES;

	void printInfo( void ); 
};

#endif

