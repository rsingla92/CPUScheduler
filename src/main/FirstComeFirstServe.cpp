/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "FirstComeFirstServe.hpp"

FirstComeFirstServe::FirstComeFirstServe(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make a FCFS object" << std::endl;
}

std::vector<ProcessControlBlock> FirstComeFirstServe::getFinalQueueOrder()
{
	return _readyQueue;
}


void FirstComeFirstServe::run() {
	int firstTimeSlice = 0;

	populateInitialQueues( isHigherPriority );
	//printInfo();
	printInfo();
	printIOWaitingInfo();
	printTARQInfo();

	/* Loop until the algorithm is done */
	while( true ) {
		checkWaitingProcesses(); // if _readyQueue is empty, pass minimum time in IO or Waiting to fill _readyQueue
		if( _readyQueue.size() == 0 ) break;

		/* Split the next CPU burst of the ready queue (if it has not already been) into time slices */
		breakUpCPUBurst( _readyQueue[0] );

		printInfo();
		printIOWaitingInfo();
		printTARQInfo();

		if( _readyQueue[0].getCPUQuantumVec().size() != 0 )
		{
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


/*
void FirstComeFirstServe::run(){
	std::vector<ProcessControlBlock>::iterator it; 
	int firstTimeSlice = 0;

	populateInitialQueues( isHigherPriority ); 

	// Loop until the algorithm is done
	while( true ) {

		checkWaitingProcesses(); 
		if( _readyQueue.size() == 0 ) break;

		// Split the next CPU burst of the ready queue (if it has not already been) into time slices
		breakUpCPUBurst( _readyQueue[0] );  

		if( _readyQueue[0].getCPUQuantumVec().size() > 0 )
		{
			std::vector<int> newCPUQuantumVec = _readyQueue[0].getCPUQuantumVec();
			std::cout << "newCPUQuantumVec[0]: " << newCPUQuantumVec[0] << std::endl;
			std::vector<int> deductedCPUBurst = _readyQueue[0].getCPUBursts();
			firstTimeSlice = newCPUQuantumVec[0];
			// Remove the first element from the list of time slices
			newCPUQuantumVec.erase( newCPUQuantumVec.begin() );
			_readyQueue[0].setCPUQuantumVec( newCPUQuantumVec ); 
			// Testing
				std::cout << "FCFS -- Process: " << _readyQueue[0].getPID() <<" Time Slice: " << firstTimeSlice << std::endl;
			deductedCPUBurst[0] -= firstTimeSlice; 
			_readyQueue[0].setCPUBursts( deductedCPUBurst );
			passTimeAndCheckWaiting( firstTimeSlice ); 
		}
		//sendExecutingProcessToIO(); // send process To IO Waiting Queue
		if( _readyQueue[0].getCPUQuantumVec().size() == 0 )
		{
			sendExecutingProcessToIO();
		}
	}
} */










