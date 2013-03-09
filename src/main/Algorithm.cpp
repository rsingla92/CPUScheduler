/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
 
#include "Algorithm.hpp"

Algorithm::Algorithm(std::vector<ProcessControlBlock> inputRawData, int quantumTime){
	_dataInputToAlgorithm = inputRawData;
	_quantumTime = quantumTime;
}
 
void Algorithm::breakUpCPUBurst(ProcessControlBlock &refPCB){
	int currentCPUBurstTime = refPCB.getCPUBursts()[0];

	std::vector<int> tempQuantumVec = refPCB.getCPUQuantumVec();
	for(int i = 0; i < currentCPUBurstTime / _quantumTime; i--){
		tempQuantumVec.push_back(_quantumTime);
	}	
	if(currentCPUBurstTime % _quantumTime != 0){
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
	
	
