/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "PatientPriority.hpp"
#include <iostream>

PatientPriority::PatientPriority(std::vector<ProcessControlBlock> inputRawData, int quantumTime) : Algorithm(inputRawData, quantumTime) {
}

PatientPriority::~PatientPriority(void)
{
}

void PatientPriority::run() {
	std::vector<ProcessControlBlock>::iterator it;
    typedef std::vector<ProcessControlBlock>::size_type vec_sz;
    vec_sz checkInitialSize = 0;
	int firstTimeSlice = 0;

	populateInitialQueues( isHigherPriority ); 

	while( true ) {
		bool flagSort = false;

		checkWaitingProcesses(); 
		if( _readyQueue.size() == 0 ) break;
		
		breakUpCPUBurst( _readyQueue[0] );  

		if( _readyQueue[0].getCPUQuantumVec().size() != 0 )
		{
			checkInitialSize = _readyQueue.size();
			std::vector<int> newCPUQuantumVec = _readyQueue[0].getCPUQuantumVec();
			std::vector<int> deductedCPUBurst = _readyQueue[0].getCPUBursts();
			firstTimeSlice = _readyQueue[0].getCPUQuantumVec()[0];
			/* Remove the first element from the list of time slices */
			newCPUQuantumVec.erase( newCPUQuantumVec.begin() );
			_readyQueue[0].setCPUQuantumVec( newCPUQuantumVec ); 

			deductedCPUBurst[0] -= firstTimeSlice; 
			_readyQueue[0].setCPUBursts( deductedCPUBurst );
			passTimeAndCheckWaiting( firstTimeSlice ); 

			flagSort = ( _readyQueue.size() > checkInitialSize )?true:flagSort; 
		}

		if( _readyQueue[0].getCPUQuantumVec().size() == 0 )
		{
			sendExecutingProcessToIO(); 
		}

		if( flagSort ) {
			std::sort( _readyQueue.begin(), _readyQueue.end(), isHigherPriority );
		}
	}
}

std::vector<ProcessControlBlock> PatientPriority::getFinalQueueOrder()
{
	return _readyQueue; 
}
