/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "InstantPriority.hpp"

InstantPriority:: InstantPriority(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make an INSTP object" << std::endl;
}

void InstantPriority:: run(){
    std:: cout << "running INSTP. Im rude" << std::endl;
}

std::vector<ProcessControlBlock> InstantPriority::getFinalQueueOrder()
{
	return _readyQueue;
}