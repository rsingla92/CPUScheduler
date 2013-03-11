/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
 
#include "Algorithm.hpp"
#include <iostream>

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
	
	
