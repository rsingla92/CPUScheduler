/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "NonPreemptiveShortestJobFirst.hpp"

NonPreShortestJobFirst:: NonPreShortestJobFirst(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make an NPSJF object" << std::endl;
}

void NonPreShortestJobFirst:: run(){
    std::cout << "running NPSJP" << std::endl;
}

std::vector<ProcessControlBlock> NonPreShortestJobFirst::getFinalQueueOrder()
{
	return _readyQueue;
}