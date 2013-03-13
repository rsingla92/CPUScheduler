/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "PreShortestJobFirst.hpp"

PreShortestJobFirst:: PreShortestJobFirst(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make a SJF object" << std::endl;
}

void PreShortestJobFirst:: run(){
    std::cout << "running SJF with preemption" << std::endl;
}

std::vector<ProcessControlBlock> PreShortestJobFirst::getFinalQueueOrder()
{
	return _readyQueue;
}