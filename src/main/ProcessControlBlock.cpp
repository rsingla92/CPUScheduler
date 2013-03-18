/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "ProcessControlBlock.hpp"

const float ProcessControlBlock::INIT_BURST_ESTIMATE = 10.0;

ProcessControlBlock::ProcessControlBlock(): _pid(-1), _tarq(-1), _prio(-1),
                        _tncpu(-1), _burstavg(INIT_BURST_ESTIMATE), _waitTime(0), _IOTime(0), _agingPriorityOffset(0), _agingTimeOffset(1)
{
}

ProcessControlBlock::ProcessControlBlock(int PID, int TARQ, int PRIO, int TNCPU,
                        std::vector<int> CPUBursts, std::vector<int>IOBursts):
                        _pid(PID), _tarq(TARQ), _prio(PRIO), _tncpu(TNCPU),_burstavg(INIT_BURST_ESTIMATE), _waitTime(0), _IOTime(0),
                        _CPUBursts(CPUBursts),_IOBursts(IOBursts), _agingTimeOffset(1), _agingPriorityOffset(0)
{
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

int ProcessControlBlock::getWaitTime() const {
	return _waitTime;
}

void ProcessControlBlock::setWaitTime(int waitTime){
	_waitTime = waitTime;
}

int ProcessControlBlock::getIOTime() const{
	return _IOTime;
}

void ProcessControlBlock::setIOTime(int IOTime){
	_IOTime = IOTime;
}

void ProcessControlBlock::calculateAverageBurst( float alpha, int lastBurst ) {
	_burstavg = alpha*lastBurst + _burstavg*(1-alpha); 
}

void ProcessControlBlock::setAgingTimeOffset(int offset){
    _agingTimeOffset = offset;
}

int ProcessControlBlock::getAgingTimeOffset() const{
    return _agingTimeOffset;
}

void ProcessControlBlock::setAgingPriorityOffset(int offset){
    _agingPriorityOffset = offset;
}

int ProcessControlBlock::getAgingPriorityOffset() const{
    return _agingPriorityOffset;
}

void ProcessControlBlock::revertAgingDefault() {
    _agingPriorityOffset = 0;
    _agingTimeOffset = 1;
}