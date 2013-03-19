/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "FirstComeFirstServe.hpp"

FirstComeFirstServe::FirstComeFirstServe(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
}

void FirstComeFirstServe::run() {
    
	int firstTimeSlice = 0;
	int pastReadyQueueSize = 0;

	populateInitialQueues( isHigherPriority );

	while( true ) {
		checkWaitingProcesses();
		if( _readyQueue.size() == 0 ) break;

		breakUpCPUBurst( _readyQueue[0] );

		if( _readyQueue[0].getCPUQuantumVec().size() != 0 )
		{
			std::vector<int> newCPUQuantumVec = _readyQueue[0].getCPUQuantumVec();
			std::vector<int> deductedCPUBurst = _readyQueue[0].getCPUBursts();
			firstTimeSlice = _readyQueue[0].getCPUQuantumVec()[0];
			/* Remove the first element from the list of time slices */
			newCPUQuantumVec.erase( newCPUQuantumVec.begin() );
			_readyQueue[0].setCPUQuantumVec( newCPUQuantumVec );

			deductedCPUBurst[0] -= firstTimeSlice;
			_readyQueue[0].setCPUBursts( deductedCPUBurst );
			pastReadyQueueSize = _readyQueue.size();
			passTimeAndCheckWaiting( firstTimeSlice );
			if(_readyQueue.size() - pastReadyQueueSize > 0) {
				std::sort(_readyQueue.begin()+pastReadyQueueSize, _readyQueue.end(), arrivesEarlier);
			}

		}

		if( _readyQueue[0].getCPUQuantumVec().size() == 0 ) // current CPU Burst has completed, send to IO queue
		{
			sendExecutingProcessToIO();
		}
		else // current CPU Burst has more time - push to back of ready queue
		{
			_readyQueue.push_back(_readyQueue[0]);
			_readyQueue.erase(_readyQueue.begin());
		}
	}
}


