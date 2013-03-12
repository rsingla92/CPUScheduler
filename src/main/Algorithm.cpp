/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "Algorithm.hpp"

const int Algorithm::NO_WAITING_PROCESSES = -1;

Algorithm::Algorithm(std::vector<ProcessControlBlock> inputRawData, int quantumTime)
: _dataInputToAlgorithm(inputRawData), _quantumTime(quantumTime)
{
}

/*
 * Function: breakUpCPUBurst
 * Parameters: refPCB - The PCB of the process.
 * Returns: Nothing
 * Purpose: Splits up the next CPU burst of the process referenced by refPCB into smaller CPU bursts
 *          based on the quantum time parameter. This is used by the pre-emptive algorithms.
 */
void Algorithm::breakUpCPUBurst(ProcessControlBlock &refPCB){
	int currentCPUBurstTime = refPCB.getCPUBursts()[0];
	std::vector<int> tempQuantumVec;
    
	for(int i = 0; i < currentCPUBurstTime / _quantumTime; i++) {
		tempQuantumVec.push_back(_quantumTime);
	}
    
	if(currentCPUBurstTime % _quantumTime != 0) {
		tempQuantumVec.push_back(currentCPUBurstTime % _quantumTime);
	}
    
	refPCB.setCPUQuantumVec(tempQuantumVec);
	
	return;
}

void Algorithm::setQuantumTime(int newQTime){
	_quantumTime = newQTime;
	return;
}

int Algorithm::getQuantumTime(){
	return _quantumTime;
}

/*
 * Function: populateInitialQueues
 * Parameters: None
 * Returns: Nothing
 * Purpose: Fills the ready queue and the TARQ with processes. Any processes that have not arrived yet (they have
 *          a non-zero arrival time) are put in the TARQ; processes that are ready (have an arrival time of 0) are
 *          put in the Ready queue. Both queues are then sorted.
 */
void Algorithm::populateInitialQueues( bool (*predicate)(const ProcessControlBlock&, const ProcessControlBlock&) )
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
	std::sort( _readyQueue.begin(), _readyQueue.end(), predicate );
    
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
void Algorithm::passTimeAndCheckWaiting( int time ) {
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
void Algorithm::checkWaitingProcesses( void ) {
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
int Algorithm::getMinimumWaitIndex( void )
{
	int minTARQVal = 0, minIOVal = 0;
	std::vector<ProcessControlBlock>::iterator tarqIt;
	std::vector<ProcessControlBlock>::iterator ioIt;
    
	if( _TimeArrivalReadyQueue.size() == 0 && _IOWaitingQueue.size() == 0 ) return NO_WAITING_PROCESSES;
	
	/* There are waiting processes */
	if( _TimeArrivalReadyQueue.size() > 0 ) {
		tarqIt = std::min_element( _TimeArrivalReadyQueue.begin(), _TimeArrivalReadyQueue.end(), isLowerTarq );
		minTARQVal = tarqIt->getTARQ();
	}
	else {
		minTARQVal = 0;
	}
    
	if( _IOWaitingQueue.size() > 0 && _IOWaitingQueue[0].getIOBursts().size() > 0 ) {
		ioIt = std::min_element( _IOWaitingQueue.begin(), _IOWaitingQueue.end(), isFirstIOBurstLess );
		minIOVal = ioIt->getIOBursts()[0]; 
	}
	else
	{
		minIOVal = 0;
	}
    
	return std::min( minTARQVal, minIOVal );
}