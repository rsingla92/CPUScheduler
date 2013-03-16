/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#ifndef PATIENT_PRIORITY_H
#define PATIENT_PRIORITY_H

#include "Algorithm.hpp"

class PatientPriority :
   public Algorithm
{
public:
	PatientPriority(std::vector<ProcessControlBlock> inputRawData, int quantumTime);
	~PatientPriority( void );

	void run();
	std::vector<ProcessControlBlock> getFinalQueueOrder();

private: 
	/* Constants used by the class */
	static const int NO_WAITING_PROCESSES;
};

#endif

