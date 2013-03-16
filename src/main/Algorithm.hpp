/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#ifndef ALGORITHM_H
#define ALGORITHM_H
 
 
#include "ProcessControlBlock.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
 
class Algorithm{
public:
	Algorithm(std::vector<ProcessControlBlock> inputRawData, int quantumTime, double alpha = 1.0);
	Algorithm(std::vector<ProcessControlBlock> inputRawData);
	virtual ~Algorithm(){};

	virtual void run() = 0;
	virtual std::vector<ProcessControlBlock> getFinalQueueOrder() = 0;
    
protected:
	void breakUpCPUBurst(ProcessControlBlock &refPCB);
	void setQuantumTime(int newQTime);
	int getQuantumTime();
	void setAlpha( int newAlpha );
	float getAlpha( void ) const;
	void populateInitialQueues(  bool (*predicate)(const ProcessControlBlock&, const ProcessControlBlock&) ); 
	void passTimeAndCheckWaiting( int time );
	int getMinimumWaitIndex( void );
	void checkWaitingProcesses( void );
	void sendExecutingProcessToIO( void ); 
	void printInfo( void ); 
	void preempt( bool (*predicate)(const ProcessControlBlock&, const ProcessControlBlock&) );

	std::vector<ProcessControlBlock> _dataInputToAlgorithm;
	std::vector<ProcessControlBlock> _readyQueue; 
	std::vector<ProcessControlBlock> _IOWaitingQueue;
	std::vector<ProcessControlBlock> _TimeArrivalReadyQueue;

private:
	std::vector<ProcessControlBlock> _finalQueueOrder;	
	int _quantumTime;
	float _alpha;

	/* Constants */
	static const int NO_WAITING_PROCESSES;
};

#endif
