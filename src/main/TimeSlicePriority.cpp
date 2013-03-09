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