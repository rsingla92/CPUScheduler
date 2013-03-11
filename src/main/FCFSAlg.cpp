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
	for(int i = 0; i < _dataInputToAlgorithm.size(); i++){
		if(_dataInputToAlgorithm[i].getArrivalTime() > 0){
			_readyQueue.push_back(_dataInputToAlgorithm[i]);
		}
		else
		{
			_timeArrivalReadyQueue.push_back(_dataInputToAlgorithm[i]);
		}
	}
	assert(_timeArrivalReadyQueue.size() + _readyQueue.size() + _IOWaitingQueue.size() == _dataInputToAlgorithm.size());
	
	//Need to Order the ready queue properly here.
	_readyQueue.sort(_readyQueue.begin(), _readyQueue.end(), priorityLowToHigh);
	
	return;
}
