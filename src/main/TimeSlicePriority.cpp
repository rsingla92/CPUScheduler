/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "TimeSlicePriority.hpp"
#include <iostream>

const int TimeSlicePriority::NO_WAITING_PROCESSES = -1;

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

	populateInitialQueues(); 

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

			if( _readyQueue.size() != checkInitialSize ) {
				/* New processes were added to _readyQueue, must re-order queue (based on priority) */
				flagSort = true; 
			}
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

/*
 * Function: populateInitialQueues
 * Parameters: None
 * Returns: Nothing
 * Purpose: Fills the ready queue and the TARQ with processes. Any processes that have not arrived yet (they have 
 *          a non-zero arrival time) are put in the TARQ; processes that are ready (have an arrival time of 0) are 
 *          put in the Ready queue. Both queues are then sorted. 
 */
void TimeSlicePriority::populateInitialQueues( void )
{
	std::vector<ProcessControlBlock>::iterator it;

	for( it = _dataInputToAlgorithm.begin(); it != _dataInputToAlgorithm.end(); ++it ) 
	{
		if( it->getTARQ() <= 0 ) 
		{
			/* The process is already ready -- add to ready queue. */
			_readyQueue.push_back( *it ); 
		}
		else 
		{
			/* The process has not yet arrived; add it to TARQ */
			_TimeArrivalReadyQueue.push_back( *it ); 
		}
	}

	/* Sort in order of priority. */
	std::sort( _readyQueue.begin(), _readyQueue.end(), isHigherPriority ); 

	/* Sort the TARQ - minimum arrival times will be at the front. */
	std::sort( _TimeArrivalReadyQueue.begin(), _TimeArrivalReadyQueue.end(), arrivesEarlier ); 
}

/*
 * Function: passTimeAndCheckWaiting
 * Parameters: None
 * Returns: Nothing
 * Purpose: Deducts time from the processes waiting in the IO/TARQ queues and checks if any
 * need to be added to the ready queue. 
 */
void TimeSlicePriority::passTimeAndCheckWaiting( int time ) {
	std::vector<ProcessControlBlock>::iterator it;
	std::vector<int> newIOBurstQueue;

	if( _TimeArrivalReadyQueue.size() == 0 && _IOWaitingQueue.size() == 0 ) return;

	/* Go through the TARQ and IO queues to remove that minimum waiting time */
	for( it = _TimeArrivalReadyQueue.begin(); it != _TimeArrivalReadyQueue.end(); ++it ) {
		it->setTARQ( it->getTARQ() - time ); 

		if( it->getTARQ() <= 0 ) {
			/* This process is ready to be sent to the ready queue. */
			_readyQueue.push_back( *it ); 
		}
	}

	/* Go through the IO queue and take away the time from the waiting time of the processes */ 
	for( it = _IOWaitingQueue.begin(); it != _IOWaitingQueue.end(); ++it ) {
		newIOBurstQueue = it->getIOBursts(); 
		if( newIOBurstQueue.size() != 0 ) {
			newIOBurstQueue[0] -= time; 

			it->setIOBursts( newIOBurstQueue );

			if( newIOBurstQueue[0] <= 0 ) {
				/* Process is ready to be sent to the ready queue */
				_readyQueue.push_back( *it ); 
			}
		}
	}

	/* Remove any processes that are no longer waiting from the TARQ/IO Queues */
	_TimeArrivalReadyQueue.erase( std::remove_if( _TimeArrivalReadyQueue.begin(), _TimeArrivalReadyQueue.end(), checkToRemoveTARQ ), 
			_TimeArrivalReadyQueue.end() );

	_IOWaitingQueue.erase( std::remove_if( _IOWaitingQueue.begin(), _IOWaitingQueue.end(), checkToRemoveIO ), 
			_IOWaitingQueue.end() );
}

/*
 * Function: checkWaitingProcesses
 * Parameters: None
 * Returns: Nothing
 * Purpose: Checks if all of the processes are waiting. If so, subtract the waiting time of the process 
 * from the waiting times of all other processes (simulates the time passing) and place any ones that are finished
 * waiting in the ready queue.
 */
void TimeSlicePriority::checkWaitingProcesses( void ) {
	int minimumWait = 0;
	std::vector<ProcessControlBlock>::iterator it;
	std::vector<int> newIOBurstQueue;
	if( _readyQueue.size() != 0 ) return; 

	/* There is nothing in the ready queue; find the minimum waiting time from the TARQ and IO queues. */
	minimumWait = getMinimumWaitIndex(); 
	/* Add any processes that are done waiting to the ready queue */
	passTimeAndCheckWaiting( minimumWait ); 
}

/*
 * Function: getMinimumWaitIndex
 * Parameters: None
 * Returns: A 
 * Purpose: Get the index of the minimum waiting time of the two waiting queues.
 */
int TimeSlicePriority::getMinimumWaitIndex( void )
{
	int minIndex = 0;
	int minTARQVal = 0, minIOVal = 0; 
	std::vector<ProcessControlBlock>::iterator it;
	std::vector<ProcessControlBlock>::iterator minIt;

	if( _TimeArrivalReadyQueue.size() == 0 && _IOWaitingQueue.size() == 0 ) return NO_WAITING_PROCESSES; 
	
	/* There are waiting processes */
	for( it = _TimeArrivalReadyQueue.begin(), minIt = _TimeArrivalReadyQueue.begin(); 
			it != _TimeArrivalReadyQueue.end(); ++it ) {
		if( it->getTARQ() < minIt->getTARQ()) {
			minIt = it;  
			minTARQVal = minIt->getTARQ();
		}
	}

	for( it = _IOWaitingQueue.begin(), minIt = _IOWaitingQueue.begin();
		it != _IOWaitingQueue.end(); ++it ) {
		if( it->getIOBursts().size() == 0 ) continue;
		if( minIt->getIOBursts().size() == 0 || (it->getIOBursts().at(0) < minIt->getIOBursts().at(0) ) ) {
			minIt = it;
			minIOVal = minIt->getIOBursts().at(0); 
		}
	}

	return std::min( minTARQVal, minIOVal );
}
