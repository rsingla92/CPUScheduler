/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "NonPreemptivePriority.hpp"

NonPreemptivePriority:: NonPreemptivePriority(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make an NPP object" << std::endl;
}

void NonPreemptivePriority:: run(){
    std::cout << "running NPP. NOBODY CUTS ME OOOFFF" << std::endl;
}

std::vector<ProcessControlBlock> NonPreemptivePriority::getFinalQueueOrder()
{
	return _readyQueue;
}