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

void FirstComeFirstServe::run(){
	std::vector<ProcessControlBlock>::iterator it; 
	int firstTimeSlice = 0;

	populateInitialQueues( isHigherPriority ); 

	/* Loop until the algorithm is done */
	while( true ) {

		checkWaitingProcesses(); 
		if( _readyQueue.size() == 0 ) break;

		/* Split the next CPU burst of the ready queue (if it has not already been) into time slices */
		breakUpCPUBurst( _readyQueue[0] );  

		if( _readyQueue[0].getCPUQuantumVec().size() != 0 )
		{
			int checkInitialSize = _readyQueue.size();
			std::vector<int> newCPUQuantumVec = _readyQueue[0].getCPUQuantumVec();
			std::vector<int> deductedCPUBurst = _readyQueue[0].getCPUBursts();
			firstTimeSlice = newCPUQuantumVec[0];
			/* Remove the first element from the list of time slices */
			newCPUQuantumVec.erase( newCPUQuantumVec.begin() );
			_readyQueue[0].setCPUQuantumVec( newCPUQuantumVec ); 
			/** Testing **/ std::cout << "FCFS -- Process: " << _readyQueue[0].getPID() <<" Time Slice: " << firstTimeSlice << std::endl; 
			deductedCPUBurst[0] -= firstTimeSlice; 
			_readyQueue[0].setCPUBursts( deductedCPUBurst );
			passTimeAndCheckWaiting( firstTimeSlice ); 

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
	}
}


////Runs Round Robin and FCFS Algorithm, using the quantum time as the defining variable
//void FCFSAlg::run()
//{
//	int IdleCPUTime = 0; //record amount of time that CPU is not being used
//	std::vector<int> newCPUQuantumVec;
//	std::vector<int> deductedCPUBurst;
//	
//	// setup _ReadyQueue and TimeArrivalReadyQueue 
//	populateInitialQueues(&isHigherPriority); 
//	
//	while(_readyQueue.size() > 0 || _IOWaitingQueue.size() > 0 || _timeArrivalReadyQueue.size() > 0){
//		//loop while there are still processes to be handled
//		
//		checkWaitingProcesses(); 
//		
//		breakUpCPUBurst(_readyQueue[0]); 
//		newCPUQuantumVec = _readyQueue[0].getCPUQuantumVec/();
//		deductedCPUBurst = _readyQueue[0].getCPUBursts();
//
//		if(newCPUQuantumVec[0] < this->getQuantumTime()){
//			IdleCPUTime += this->getQuantumTime() - newCPUQuantumVec[0];
//		}
//		//remove first element of QuantumVec to simulate timeslice passing for CPU
//		erase(newCPUQuantumVec[0]);
//		deductedCPUBurst[0] -=
//		
//		if(newCPUQuantumVec.size() > 0){ //at least 1 timeslice of CPU time required by this CPU Burst
//			//put into back of readyQueue
//			erase(_readyQueue[0]);
//			_readyQueue.push_back(newCPUQuantumVec);
//		}
//		else{ 
//			if(_readyQueue[0].getCPUBursts().size() > 0){ // at least 1 more CPU burst left, so move to IO queue
//				erase(_readyQueue[0]);
//				_IOWaitingQueue.push_back(newCPUQuantumVec);
//			}
//			else{ //process is done, delete from readyQueue and effectively kill it
//				erase(_readyQueue[0]);
//			}
//		}						
//	}
//	
//	return;
//}
