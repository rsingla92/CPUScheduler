/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "NonPreemptiveShortestPreviousBursts.hpp"

NonPreemptiveShortestPreviousBursts:: NonPreemptiveShortestPreviousBursts(std::vector<ProcessControlBlock> rawData, float alpha ) : Algorithm(rawData, 0, alpha){
    //std::cout << "make a SPB object" << std::endl;
}

void NonPreemptiveShortestPreviousBursts:: run(){
    //std::cout << "running SPB" << std::endl;

	typedef std::vector<ProcessControlBlock>::size_type vec_sz;
	vec_sz initialSize = 0;
	std::vector<ProcessControlBlock>::iterator it;

	populateInitialQueues( isShorterPreviousCPUAvg ); 

	while( true ) {
		checkWaitingProcesses();

		if( _readyQueue.size() == 0 ) break; 

		if( _readyQueue[0].getCPUBursts().size() != 0 ) {
			initialSize = _readyQueue.size(); 
			std::vector<int> cpuBursts = _readyQueue[0].getCPUBursts(); 

			/* Send the next process to be executed -- pass the execution time */
			passTimeAndCheckWaiting( cpuBursts[0] ); 
			
			/* Send the process that has finished executing for its next IO burst */
			sendExecutingProcessToIO(); 

			if( _readyQueue.size() >= initialSize ) {
				/* A process has entered the ready queue */
				std::sort( _readyQueue.begin(), _readyQueue.end(), isShorterPreviousCPUAvg ); 
			}
		}
	}
}

std::vector<ProcessControlBlock> NonPreemptiveShortestPreviousBursts::getFinalQueueOrder()
{
	return _readyQueue;
}
