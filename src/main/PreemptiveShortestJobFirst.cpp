/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "PreemptiveShortestJobFirst.hpp"

using std::cout;
using std::endl;
using std::vector;

PreemptiveShortestJobFirst::PreemptiveShortestJobFirst(std::vector<ProcessControlBlock> rawData, bool aging) : Algorithm(rawData, 0, aging){
}

void PreemptiveShortestJobFirst::run(){
    
    populateInitialQueues(isShorterCPUBurst);
    
    while (true){
        checkWaitingProcesses();
        if(_readyQueue.size() == 0) break;
        
        if(_readyQueue[0].getCPUBursts().size() != 0){
            vector<ProcessControlBlock>::size_type oldReadyQSize = _readyQueue.size();
            preempt(isShorterCPUBurst);
            
            if(_readyQueue.size() >= oldReadyQSize){
                std::sort(_readyQueue.begin(), _readyQueue.end(), isShorterCPUBurst);
            }
        }
    }
}
