/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "PreemptiveShortestPreviousBursts.hpp"

PreemptiveShortestPreviousBursts::PreemptiveShortestPreviousBursts(std::vector<ProcessControlBlock> rawData,bool aging,  float alpha) : Algorithm(rawData, 0, aging, alpha){
}

void PreemptiveShortestPreviousBursts:: run(){
    
	typedef std::vector<ProcessControlBlock>::size_type vec_sz;
	vec_sz initialSize = 0;
	std::vector<ProcessControlBlock>::iterator it;

	populateInitialQueues(isShorterPreviousCPUAvg);

	while(true){
		checkWaitingProcesses();

		if(_readyQueue.size() == 0) break;

		if(_readyQueue[0].getCPUBursts().size() != 0) {
			initialSize = _readyQueue.size();

			preempt( isShorterPreviousCPUAvg ); 

			if( _readyQueue.size() >= initialSize )  {
				std::sort( _readyQueue.begin(), _readyQueue.end(), isShorterPreviousCPUAvg);
			}
		}
	}
}
