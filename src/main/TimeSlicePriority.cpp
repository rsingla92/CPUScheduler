/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "TimeSlicePriority.hpp"
#include <iostream>

TimeSlicePriority::TimeSlicePriority(std::vector<ProcessControlBlock> inputRawData, int quantumTime) 
	: Algorithm(inputRawData, quantumTime)
{
}

TimeSlicePriority::~TimeSlicePriority(void)
{
}

void TimeSlicePriority::run() {
	std::vector<ProcessControlBlock>::iterator it; 
	int firstTimeSlice = 0;

	populateInitialQueues( isHigherPriority ); 

	/* Loop until the algorithm is done */
	while( true ) {
		bool flagSort = false;

		checkWaitingProcesses(); 
		if( _readyQueue.size() == 0 ) break;

		/* Split the next CPU burst of the ready queue (if it has not already been) into time slices */
		breakUpCPUBurst( _readyQueue[0] );  

		if( _readyQueue[0].getCPUQuantumVec().size() != 0 )
		{
			int checkInitialSize = _readyQueue.size();
			std::vector<int> newCPUQuantumVec = _readyQueue[0].getCPUQuantumVec();
			std::vector<int> deductedCPUBurst = _readyQueue[0].getCPUBursts();
			firstTimeSlice = _readyQueue[0].getCPUQuantumVec()[0];
			/* Remove the first element from the list of time slices */
			newCPUQuantumVec.erase( newCPUQuantumVec.begin() );
			_readyQueue[0].setCPUQuantumVec( newCPUQuantumVec ); 
			/** Testing **/ std::cout << "Process: " << _readyQueue[0].getPID() <<" Time Slice: " << firstTimeSlice << std::endl; 
			deductedCPUBurst[0] -= firstTimeSlice; 
			_readyQueue[0].setCPUBursts( deductedCPUBurst );
			passTimeAndCheckWaiting( firstTimeSlice ); 

			flagSort = ( _readyQueue.size() > checkInitialSize )?true:flagSort; 
		}

		if( _readyQueue[0].getCPUQuantumVec().size() == 0 )
		{
			std::vector<int> newCPUBurstsVec = _readyQueue[0].getCPUBursts();
			/* Nothing left in the time slice list, can pop out this CPU burst and send process to IO queue */
			newCPUBurstsVec.erase( newCPUBurstsVec.begin() );

			_readyQueue[0].setCPUBursts( newCPUBurstsVec ); 

			if( _readyQueue[0].getCPUBursts().size() != 0 ) {
				_IOWaitingQueue.push_back( _readyQueue[0] );
			}

			_readyQueue.erase( _readyQueue.begin() );
		}

		if( flagSort ) {
			std::sort( _readyQueue.begin(), _readyQueue.end(), isHigherPriority );
		}
	}
}

std::vector<ProcessControlBlock> TimeSlicePriority::getFinalQueueOrder()
{
	return _readyQueue; 
}
