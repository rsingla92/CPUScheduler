/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "ProcessControlBlock.hpp"

const float ProcessControlBlock::INIT_BURST_ESTIMATE = 10.0;

ProcessControlBlock::ProcessControlBlock(): _pid(-1), _tarq(-1), _prio(-1),
                        _tncpu(-1), _burstavg(INIT_BURST_ESTIMATE)
{
}

ProcessControlBlock::ProcessControlBlock(int PID, int TARQ, int PRIO, int TNCPU,
                        std::vector<int> CPUBursts, std::vector<int>IOBursts):
                        _pid(PID), _tarq(TARQ), _prio(PRIO), _tncpu(TNCPU),
                        _CPUBursts(CPUBursts),_IOBursts(IOBursts), _burstavg(INIT_BURST_ESTIMATE)
{
}

ProcessControlBlock& ProcessControlBlock::operator=(const ProcessControlBlock& otherProcess)
{
    if (&otherProcess != this)
    {
        this->_pid = otherProcess._pid;
        this->_tarq = otherProcess._tarq;
        this->_prio = otherProcess._prio;
        this->_tncpu = otherProcess._tncpu;
        this->_CPUBursts = otherProcess._CPUBursts;
        this->_IOBursts = otherProcess._IOBursts;
		this->_burstavg = otherProcess._burstavg; 
    }
    return *this;
}

int ProcessControlBlock::getPID() const
{
   return _pid;
}
void ProcessControlBlock::setPID(int PID)
{
	_pid = PID;
}

int ProcessControlBlock::getTARQ() const
{
    return _tarq;
}

void ProcessControlBlock::setTARQ(int TARQ)
{
    _tarq = TARQ;
}

int ProcessControlBlock::getPriority() const
{
    return _prio;
}

void ProcessControlBlock::setPriority(int PRIO)
{
    _prio = PRIO;
}

int ProcessControlBlock::getTNCPU() const
{
    return _tncpu;
}

void ProcessControlBlock::setTNCPU(int TNCPU)
{
    _tncpu = TNCPU;
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

void ProcessControlBlock::setFirstCPUBurst( int burst ) {
	if( _CPUBursts.size() == 0 ) return;
	_CPUBursts[0] = burst; 
}

PCB_STATES ProcessControlBlock::getState() const {
	return _state;
}

void ProcessControlBlock::setState( PCB_STATES state ) {
	_state = state; 
}

float ProcessControlBlock::getBurstAvg() const {
	return _burstavg;
}

void ProcessControlBlock::setBurstAvg( float burstAvg ) {
	_burstavg = burstAvg; 
}

void ProcessControlBlock::calculateAverageBurst( float alpha, int lastBurst ) {
	_burstavg = alpha*lastBurst + _burstavg*(1-alpha); 
}