/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "PreemptiveShortestPreviousBursts.hpp"

PreemptiveShortestPreviousBursts:: PreemptiveShortestPreviousBursts(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make a PSPB object" << std::endl;
}

void PreemptiveShortestPreviousBursts:: run(){
    std::cout << "running PSPB" << std::endl;
}

std::vector<ProcessControlBlock> PreemptiveShortestPreviousBursts::getFinalQueueOrder()
{
	return _readyQueue;
}