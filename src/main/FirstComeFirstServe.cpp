/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "FirstComeFirstServe.hpp"

FirstComeFirstServe::FirstComeFirstServe(std::vector<ProcessControlBlock> rawData) : Algorithm(rawData, 0){
    std::cout << "make a FCFS object" << std::endl;
}

void FirstComeFirstServe:: run(){
    std:: cout << "running FCFS" << std:: endl;
}

std::vector<ProcessControlBlock> FirstComeFirstServe::getFinalQueueOrder()
{
	return _readyQueue;
}