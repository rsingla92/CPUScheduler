/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "NonPreemptiveShortestPreviousBursts.hpp"

NonPreemptiveShortestPreviousBursts:: NonPreemptiveShortestPreviousBursts(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make a SPB object" << std::endl;
}

void NonPreemptiveShortestPreviousBursts:: run(){
    std::cout << "running SPB" << std::endl;
}

std::vector<ProcessControlBlock> NonPreemptiveShortestPreviousBursts::getFinalQueueOrder()
{
	return _readyQueue;
}