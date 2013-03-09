#include "processcontrolblock.hpp"

int ProcessControlBlock::getPID() const
{
   return _pid;
}
void ProcessControlBlock::setPID(int PID)
{
	_pid = PID;
}

std::vector<int> ProcessControlBlock::getCPUBursts() const
{
	return _CPUBursts;
}

void ProcessControlBlock::setCPUBursts(std::vector<int> CPUBursts)
{
	_CPUBursts = CPUBursts;
	return;
}
  
std::vector<int> ProcessControlBlock::getIOBursts() const
{
	return _IOBursts;
}

void ProcessControlBlock::setIOBursts(std::vector<int> IOBursts)
{
	_IOBursts = IOBursts;
	return;
}
   
std::vector<int> ProcessControlBlock::getCPUQuantumVec() const
{
	return _CPUQuantumVec;
}

void ProcessControlBlock::setCPUQuantumVec(std::vector<int> CPUQuantumVec)
{
	_CPUQuantumVec = CPUQuantumVec;
	return;
}

int ProcessControlBlock::getTimeOfArrival() const
{
	return _timeOfArrival;
}

void ProcessControlBlock::setTimeOfArrival( int timeOfArrival )
{
	_timeOfArrival = timeOfArrival; 
}

int ProcessControlBlock::getPriority() const
{
	return _priority;
}

void ProcessControlBlock::setPriority( int priority )
{
	_priority = priority;
}