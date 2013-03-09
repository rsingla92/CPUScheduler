/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "TimeSlicePriority.hpp"


TimeSlicePriority::TimeSlicePriority(std::vector<ProcessControlBlock> inputRawData, int quantumTime) 
	: Algorithm(inputRawData, quantumTime)
{
}


TimeSlicePriority::~TimeSlicePriority(void)
{
}

void TimeSlicePriority::run()
{

}

std::vector<ProcessControlBlock> TimeSlicePriority::getFinalQueueOrder()
{
	return _readyQueue; 
}

// Use _dataInputToAlgorithm to fill _readyQueue and _TimeArrivalReadyQueue
void TimeSlicePriority::populateInitialQueues( void )
{
	std::vector<ProcessControlBlock>::iterator it;

	for( it = _dataInputToAlgorithm.begin(); it != _dataInputToAlgorithm.end(); ++it ) 
	{
		if( it->getTimeOfArrival() <= 0 ) 
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