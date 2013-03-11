#include "processcontrolblock.hpp"

int ProcessControlBlock::getPID()
{
   return _pid;
}
void ProcessControlBlock::setPID(int PID)
{
	_pid = PID;
}

int ProcessControlBlock::getArrivalTime()
{
	return _arrivalTime;
}

void ProcessControlBlock::setArrivalTime(int arrivalTime)
{
	_arrivalTime = arrivalTime;
	return;
}

std::vector<int> ProcessControlBlock::getCPUBursts()
{
	return _CPUBursts;
}

void ProcessControlBlock::setCPUBursts(std::vector<int> CPUBursts)
{
	_CPUBursts = CPUBursts;
	return;
}
  
std::vector<int> ProcessControlBlock::getIOBursts()
{
	return _IOBursts;
}

void ProcessControlBlock::setIOBursts(std::vector<int> IOBursts)
{
	_IOBursts = IOBursts;
	return;
}
   
std::vector<int> ProcessControlBlock::getCPUQuantumVec()
{
	return _CPUQuantumVec;
}

void ProcessControlBlock::setCPUQuantumVec(std::vector<int> CPUQuantumVec)
{
	_CPUQuantumVec = CPUQuantumVec;
	return;
}
