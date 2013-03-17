/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "Algorithm.hpp"

const int Algorithm::NO_WAITING_PROCESSES = -1;

Algorithm::Algorithm(std::vector<ProcessControlBlock> inputRawData, int quantumTime, double alpha)
: _dataInputToAlgorithm(inputRawData), _quantumTime(quantumTime), _alpha(alpha)
{
}

Algorithm::Algorithm(std::vector<ProcessControlBlock> inputRawData) : _dataInputToAlgorithm(inputRawData), _quantumTime(0), _alpha(1.0) { 
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
			it->setState( READY );
			_readyQueue.push_back( *it ); 
		}
		else
		{
			/* The process has not yet arrived; add it to TARQ */
			it->setState( NEW );
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
			it->setState( READY );
			_readyQueue.push_back( *it );
		}
	}
    
	/* Go through the IO queue and take away the time from the waiting time of the processes */
	for( it = _IOWaitingQueue.begin(); it != _IOWaitingQueue.end(); ++it ) {
		newIOBurstQueue = it->getIOBursts();
		if( newIOBurstQueue.size() != 0 ) {
			newIOBurstQueue[0] -= time; 

			if( newIOBurstQueue[0] <= 0 ) {
				/* Process is ready to be sent to the ready queue */
				newIOBurstQueue.erase( newIOBurstQueue.begin() );
				it->setIOBursts( newIOBurstQueue );
				it->setState( READY );
				_readyQueue.push_back( *it ); 
			}
			else
			{ 
				it->setState(WAITING);
				it->setIOBursts( newIOBurstQueue );
			}
		}
	}
    
	/* Remove any processes that are no longer waiting from the TARQ/IO Queues */
	_TimeArrivalReadyQueue.erase( std::remove_if( _TimeArrivalReadyQueue.begin(), _TimeArrivalReadyQueue.end(), checkToRemoveWaiting ), 
			_TimeArrivalReadyQueue.end() );

	_IOWaitingQueue.erase( std::remove_if( _IOWaitingQueue.begin(), _IOWaitingQueue.end(), checkToRemoveWaiting ), 
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
	if(minimumWait == NO_WAITING_PROCESSES){
		return;
	}
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
	int minTARQVal = -1, minIOVal = -1; 
	std::vector<ProcessControlBlock>::iterator tarqIt;
	std::vector<ProcessControlBlock>::iterator ioIt;

	if( _TimeArrivalReadyQueue.size() == 0 && _IOWaitingQueue.size() == 0 ) return NO_WAITING_PROCESSES;
	/* There are waiting processes */
	if( _TimeArrivalReadyQueue.size() > 0 ) {
		tarqIt = std::min_element( _TimeArrivalReadyQueue.begin(), _TimeArrivalReadyQueue.end(), isLowerTarq );
		minTARQVal = tarqIt->getTARQ();
	}
	else {
		minTARQVal = -1;
	}
    
	if( _IOWaitingQueue.size() > 0 && _IOWaitingQueue[0].getIOBursts().size() > 0 ) {
		ioIt = std::min_element( _IOWaitingQueue.begin(), _IOWaitingQueue.end(), isFirstIOBurstLess );
		minIOVal = ioIt->getIOBursts()[0]; 
	}
	else
	{
		minIOVal = -1;
	}

	if( minTARQVal == -1 ) return minIOVal;
	else if( minIOVal == -1 ) return minTARQVal; 
	else return std::min( minTARQVal, minIOVal );
}

void Algorithm::sendExecutingProcessToIO( void ) {

	if( _readyQueue.size() == 0) return; 

	std::vector<int> newCPUBurstsVec = _readyQueue[0].getCPUBursts();

	/* For checking the order - testing */
	//std::cout << "PCB " << _readyQueue[0].getPID() << " bursts for " << newCPUBurstsVec[0] << ", estimated avg is " <<
	//	_readyQueue[0].getBurstAvg() << std::endl;

	/* Calculate the predicted burst time based on the history */
	_readyQueue[0].calculateAverageBurst(_alpha, newCPUBurstsVec[0] ); 

	/* Delete the first CPU burst, then send to do the IO burst */
	newCPUBurstsVec.erase( newCPUBurstsVec.begin() );

	_readyQueue[0].setCPUBursts( newCPUBurstsVec ); 

	if( _readyQueue[0].getCPUBursts().size() != 0 ) {
		_readyQueue[0].setState( WAITING ); 
		_IOWaitingQueue.push_back( _readyQueue[0] );
	}

	_readyQueue.erase( _readyQueue.begin() );
}

void Algorithm::preempt( bool (*predicate)(const ProcessControlBlock&, const ProcessControlBlock&) ) {

	if( _readyQueue.size() == 0 || _readyQueue[0].getCPUBursts().size() == 0 ) return; 

	int executingBurst = _readyQueue[0].getCPUBursts()[0]; 
	int timeToPass = 0;
	std::vector<ProcessControlBlock>::iterator minTarq = _TimeArrivalReadyQueue.end(); 
	std::vector<ProcessControlBlock>::iterator minIO = _IOWaitingQueue.end(); 
	std::vector<ProcessControlBlock>::iterator index; 
	bool preemptFlag = true;

	/* Find the process in the TARQ with the minimum arrival time that will preempt the current process
	 * in the CPU. */
	for( index = _TimeArrivalReadyQueue.begin(); index != _TimeArrivalReadyQueue.end(); ++index ) {
		if( executingBurst - index->getTARQ() > 0 ) {
			/* The PCB in the TARQ arrives before the currently executing process finishes */
			if( predicate( *index, _readyQueue[0] ) ) {
				/* The PCB in the TARQ has a higher priority than the current executing PCB */
				if( minTarq == _TimeArrivalReadyQueue.end() ) {
					minTarq = index;
				} else if(  index->getTARQ() < minTarq->getTARQ() ) {
					minTarq = index; 
				} 
			}
		}
	}

	for( index = _IOWaitingQueue.begin(); index != _IOWaitingQueue.end(); ++index ) {

		if( index->getIOBursts().size() == 0 ) continue; 

		if( executingBurst - index->getIOBursts()[0] > 0 ) {
			/* The PCB in the IO Queue finishes before the currently executing process finishes */
			if( predicate( *index, _readyQueue[0] ) ) {
				/* The PCB in the IO Queue has a higher priority than the currently executing PCB */
				if( minIO == _IOWaitingQueue.end() ) {
					minIO = index;
				} else if( index->getIOBursts()[0] < minIO->getIOBursts()[0] ) {
					minIO = index; 
				}
			}
		}
	}

	if( minTarq == _TimeArrivalReadyQueue.end() && minIO == _IOWaitingQueue.end() ) {
		/* Neither preempt the executing process */
		timeToPass = _readyQueue[0].getCPUBursts()[0]; 
		preemptFlag = false;
	} else if( minTarq == _TimeArrivalReadyQueue.end() ) {
		/* The minimum from the IO queue preempts */
		timeToPass = minIO->getIOBursts()[0]; 
	} else {
		/* The minimum from the TARQ preempts */
		timeToPass = minTarq->getTARQ(); 
	}

	std::cout << "PCB " << _readyQueue[0].getPID() << " bursts for " << timeToPass << std::endl;

	if( preemptFlag ) {
		_readyQueue[0].setFirstCPUBurst( _readyQueue[0].getCPUBursts()[0] - timeToPass ); 
		passTimeAndCheckWaiting( timeToPass ); 
	} else {
		passTimeAndCheckWaiting( timeToPass ); 
		sendExecutingProcessToIO(); 
	}
}

void Algorithm::printInfo( void ) {
	std::cout << "printing readyQueue info:" << std::endl;
	for( int i = 0; i < _readyQueue.size(); i++ ) {
		std::cout << _readyQueue[i].getPID() << std::endl; 

		for( int j = 0; j < _readyQueue[i].getCPUBursts().size(); j++ ) {
			std::cout << "CPU Burst " << j << ": "<< _readyQueue[i].getCPUBursts()[j] << std::endl;
		}

		for( int j = 0; j < _readyQueue[i].getIOBursts().size(); j++ ) {
			std::cout << "IO Burst " << j << ": "<< _readyQueue[i].getIOBursts()[j] << std::endl;
		}
	}
}


void Algorithm::printIOWaitingInfo( void ) {
	std::cout << "printing IO WaitingQueue info:" << std::endl;
	for( int i = 0; i < _IOWaitingQueue.size(); i++ ) {
		std::cout << _IOWaitingQueue[i].getPID() << std::endl;

		for( int j = 0; j < _IOWaitingQueue[i].getCPUBursts().size(); j++ ) {
			std::cout << "CPU Burst " << j << ": "<< _IOWaitingQueue[i].getCPUBursts()[j] << std::endl;
		}

		for( int j = 0; j < _IOWaitingQueue[i].getIOBursts().size(); j++ ) {
			std::cout << "IO Burst " << j << ": "<< _IOWaitingQueue[i].getIOBursts()[j] << std::endl;
		}
	}
}

void Algorithm::printTARQInfo( void ) {
	std::cout << "printing TARQ info:" << std::endl;
	for( int i = 0; i < _TimeArrivalReadyQueue.size(); i++ ) {
		std::cout << _TimeArrivalReadyQueue[i].getPID() << std::endl;

		for( int j = 0; j < _TimeArrivalReadyQueue[i].getCPUBursts().size(); j++ ) {
			std::cout << "CPU Burst " << j << ": "<< _TimeArrivalReadyQueue[i].getCPUBursts()[j] << std::endl;
		}

		for( int j = 0; j < _TimeArrivalReadyQueue[i].getIOBursts().size(); j++ ) {
			std::cout << "IO Burst " << j << ": "<< _TimeArrivalReadyQueue[i].getIOBursts()[j] << std::endl;
		}
	}
}

void Algorithm::setAlpha( int newAlpha ) {
	_alpha = newAlpha;
}

float Algorithm::getAlpha( void ) const {
	return _alpha;
}

