/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "RoundRobin.hpp"

RoundRobin:: RoundRobin(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make an RR object" << std::endl;
}

void RoundRobin:: run(){
    std:: cout << "running RR" << std:: endl;
}

std::vector<ProcessControlBlock> RoundRobin::getFinalQueueOrder()
{
	return _readyQueue;
}