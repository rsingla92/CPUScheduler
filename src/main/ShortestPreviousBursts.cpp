/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "ShortestPreviousBursts.hpp"

ShortestPreviousBursts:: ShortestPreviousBursts(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make a SJF object" << std::endl;
}

void ShortestPreviousBursts:: run(){
    std::cout << "running SJF" << std::endl;
}

std::vector<ProcessControlBlock> ShortestPreviousBursts::getFinalQueueOrder()
{
	return _readyQueue;
}