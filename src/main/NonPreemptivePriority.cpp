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
    cout << "make an NPP object" << endl;
}

void NonPreemptivePriority:: run(){
    cout << "running NPP. NOBODY CUTS ME OOOFFF" << endl;
    
    populateInitialQueues(isHigherPriority);
    
    while (true) {
        checkWaitingProcesses();
        if (_readyQueue.size() == 0) break;
        
        vector<int> newCPUBursts = _readyQueue[0].getCPUBursts();
        
        if (newCPUBursts.size() != 0){
            vector<ProcessControlBlock>::size_type oldReadyQSize = _readyQueue.size();
            // since NPP will finish CPU Burst
            passTimeAndCheckWaiting(newCPUBursts[0]);
            
            // for testing purposes
            //cout << "PID " << _readyQueue[0].getPID() << " running for " << newCPUBursts[0] << endl;
            
            if (_readyQueue.size() >= oldReadyQSize){
                std::sort(_readyQueue.begin()+1, _readyQueue.end(), isHigherPriority);
            }
            
            // for testing purposes
            for (unsigned int i=0; i< _readyQueue.size(); i++) {
                cout << "READY-Q ORDER: " << _readyQueue[i].getPID() << endl;
            }
            cout << endl;
            
            if(_readyQueue[0].getIOBursts().size() > 0){
                sendExecutingProcessToIO();
                
                for (unsigned int i = 0; i < _IOWaitingQueue.size() ; i++){
                    // for testing purposes
                    cout <<  "PID "<< _IOWaitingQueue[i].getPID() << " now in IO for " << _IOWaitingQueue[i].getIOBursts()[0] << endl;
                }
                cout << endl;
            }  
            else {
                _readyQueue.erase(_readyQueue.begin());
            }
        }
    }
}

std::vector<ProcessControlBlock> NonPreemptivePriority::getFinalQueueOrder()
{
	return _readyQueue;
}
