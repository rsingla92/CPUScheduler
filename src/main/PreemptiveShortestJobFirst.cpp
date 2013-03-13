/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "PreemptiveShortestJobFirst.hpp"

PreemptiveShortestJobFirst:: PreemptiveShortestJobFirst(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make a PSJF object" << std::endl;
}

void PreemptiveShortestJobFirst:: run(){
    std::cout << "running PSJF with preemption" << std::endl;
}

std::vector<ProcessControlBlock> PreemptiveShortestJobFirst::getFinalQueueOrder()
{
	return _readyQueue;
}