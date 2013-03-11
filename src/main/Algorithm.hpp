/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
 
#ifndef ALGORITHM_H
#define ALGORITHM_H
 
 
#include "processcontrolblock.hpp"
#include <vector>
 
 
class Algorithm{
public:
	Algorithm(std::vector<ProcessControlBlock> inputRawData, int quantumTime);
	virtual ~Algorithm(){};

protected:
	virtual void run() = 0;
	virtual ProcessControlBlock getFinalQueueOrder() = 0;
	
	void breakUpCPUBurst(ProcessControlBlock &refPCB);
	void setQuantumTime(int newQTime);
	int getQuantumTime();
	
	std::vector<ProcessControlBlock> _dataInputToAlgorithm;
	std::vector<ProcessControlBlock> _readyQueue; 
	std::vector<ProcessControlBlock> _IOWaitingQueue;
	std::vector<ProcessControlBlock> _timeArrivalReadyQueue;
	
private:
	std::vector<ProcessControlBlock> _finalQueueOrder;	
	int _quantumTime;
};

#endif
