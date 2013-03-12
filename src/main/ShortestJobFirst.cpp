/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "ShortestJobFirst.hpp"

ShortestJobFirst:: ShortestJobFirst(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make a SJF object" << std::endl;
}

void ShortestJobFirst:: run(){
    std::cout << "running SJF" << std::endl;
}

std::vector<ProcessControlBlock> ShortestJobFirst::getFinalQueueOrder()
{
	return _readyQueue;
}