/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
 
#include "Algorithm.hpp"

Algorithm::Algorithm(std::vector<ProcessControlBlock> inputRawData, int quantumTime){
	_dataInputToAlgorithm = _inputRawData;
	_quantumTime = quantumTime;
	return;
}
 
void Algortithm::breakUpCPUBurst(ProcessControlBlock &refPCB){
	int currentCPUBurstTime = refPCB._CPUBursts[0];

	for(int i = 0; i < currentCPUBurstTime / _quantumTime; i--){
		_CPUQuantumVec.push(_quantumTime);
	}	
	if(currentCPUBurstTime % _quantumTime != 0){
		_CPUQuantumVec.push(currentCPUBurstTime % _quantumTime);
	}
	
	return;
}

void Algortithm::setQuantumTime(int newQTime){
	_quantumTime = newQtime;
	return;
}

int Algortithm::getQuantumTime(){
	return _quantumTime;
}
	
	
