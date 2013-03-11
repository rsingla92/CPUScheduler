/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
 
#include "FCFSAlg.hpp"
#include "utilities.hpp"
 
//Sets up the Ready Queue, IOWaitingQueue, and the timeArrivalQueue, based on the input data.
void FCFSAlg::initializeQueues()
{	
	std::vector<ProcessControlBlock>::Iterator PCBIt;
	
	for(PCBIt = _dataInputToAlgorithm.begin(); PCBIt < _dataInputToAlgorithm.end(); ++PCBIt){
		if(PCBIt->getArrivalTime() > 0){
			_readyQueue.push_back(*PCBIt);
		}
		else
		{
			_timeArrivalReadyQueue.push_back(*PCBIt);
		}	
	}

	assert(_timeArrivalReadyQueue.size() + _readyQueue.size() + _IOWaitingQueue.size() == _dataInputToAlgorithm.size());
	
	_readyQueue.sort(_readyQueue.begin(), _readyQueue.end(), isHigherPriority);
	
	return;
}

void FCFSAlg::run()
{
	/* setup _ReadyQueue and TimeArrivalReadyQueue */
	populateInitialQueues(&isHigherPriority); 
	
	

	return;
}
