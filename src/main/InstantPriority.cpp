/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "InstantPriority.hpp"

InstantPriority:: InstantPriority(std::vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
    std::cout << "make an INSTP object" << std::endl;
}

void InstantPriority:: run(){
   typedef std::vector<ProcessControlBlock>::size_type vec_sz;
   vec_sz initialSize = 0;
   std::vector<ProcessControlBlock>::iterator it;

   populateInitialQueues(isHigherPriority);

   while(true){
       checkWaitingProcesses();

       if(_readyQueue.size() == 0) break;

       if(_readyQueue[0].getCPUBursts().size() != 0) {
           initialSize = _readyQueue.size();

           preempt( isHigherPriority ); 

		   if( _readyQueue.size() >= initialSize )  {
				   std::sort( _readyQueue.begin(), _readyQueue.end(), isHigherPriority);
		   }
       }
    }
}

std::vector<ProcessControlBlock> InstantPriority::getFinalQueueOrder()
{
	return _readyQueue;
}