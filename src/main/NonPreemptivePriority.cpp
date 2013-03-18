/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "NonPreemptivePriority.hpp"
using std::endl;
using std::cout;
using std::vector;

NonPreemptivePriority::NonPreemptivePriority(vector<ProcessControlBlock> rawData, int quantumTime) : Algorithm(rawData, quantumTime){
}

void NonPreemptivePriority:: run(){
    
    populateInitialQueues(isHigherPriority);
    
    while (true) {
        checkWaitingProcesses();
        if (_readyQueue.size() == 0) break;
        
        vector<int> newCPUBursts = _readyQueue[0].getCPUBursts();
        
        if (newCPUBursts.size() != 0){
            vector<ProcessControlBlock>::size_type oldReadyQSize = _readyQueue.size();
            // since NPP will finish CPU Burst, time to pass is the first CPUBurst
            passTimeAndCheckWaiting(newCPUBursts[0]);
            
            if (_readyQueue.size() >= oldReadyQSize){
                std::sort(_readyQueue.begin()+1, _readyQueue.end(), isHigherPriority);
            }
            
            if(_readyQueue[0].getIOBursts().size() > 0){
                sendExecutingProcessToIO();
            }  
            else {
                _readyQueue.erase(_readyQueue.begin());
            }
        }
    }
}
