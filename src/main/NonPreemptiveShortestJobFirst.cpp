/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "NonPreemptiveShortestJobFirst.hpp"
#include "Utilities.hpp"

NonPreemptiveShortestJobFirst::NonPreemptiveShortestJobFirst(std::vector<ProcessControlBlock> rawData) : Algorithm(rawData) {
}

void NonPreemptiveShortestJobFirst::run(){

   typedef std::vector<ProcessControlBlock>::size_type vec_sz;
   vec_sz initialSize = 0;
   std::vector<ProcessControlBlock>::iterator it;

   populateInitialQueues(isShorterCPUBurst);

   while(true){
       checkWaitingProcesses();

       if(_readyQueue.size() == 0) break;

       if(_readyQueue[0].getCPUBursts().size() != 0) {
           initialSize = _readyQueue.size();
           std::vector<int> cpuBursts = _readyQueue[0].getCPUBursts();
           passTimeAndCheckWaiting( cpuBursts[0] );
           sendExecutingProcessToIO();

           if( _readyQueue.size() >= initialSize )  {
               std::sort( _readyQueue.begin(), _readyQueue.end(), isShorterCPUBurst);
           }
       }
    }
}
