/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
 
#ifndef PROCESSCONTROLBLOCK_H
#define PROCESSCONTROLBLOCK_H

#include <vector>
#include <iostream>

enum PCB_STATES { NEW, READY, RUNNING, WAITING, TERMINATED }; 

class ProcessControlBlock
{
public:
    ProcessControlBlock();
    ProcessControlBlock(int PID, int TARQ, int PRIO, int TNCPU,
                            std::vector<int> CPUBursts, std::vector<int>IOBursts);
    
    ProcessControlBlock& operator=(const ProcessControlBlock& otherProcess);
    
    int getPID() const;
    void setPID(int PID);
    
    int getTARQ() const;
    void setTARQ(int TARQ);
    
    int getPriority() const;
    void setPriority(int PRIO);
    
    int getTNCPU() const;
    void setTNCPU(int TNCPU);

	float getBurstAvg() const;
	void setBurstAvg( float burstAvg ); 

	int getWaitTime() const;
	void setWaitTime(int waitTime);

	int getIOTime() const;
	void setIOTime(int IOTime);
    
	PCB_STATES getState() const;
	void setState( PCB_STATES state ); 

    std::vector<int> getCPUBursts() const;
    void setCPUBursts(std::vector<int> CPUBursts);

    std::vector<int> getIOBursts() const;
    void setIOBursts(std::vector<int> IOBursts);
   
    std::vector<int> getCPUQuantumVec() const;
    void setCPUQuantumVec(std::vector<int> CPUQuantumVec);

	void setFirstCPUBurst( int burst ); 

	void calculateAverageBurst( float alpha, int lastBurst );
    
    void setAgingIndex(int index);
    int getAgingIndex();
   
private:
    int _pid;
    int _tarq;
    int _prio;
    int _tncpu;
    float _burstavg; 
    int _waitTime;
    int _IOTime;
    PCB_STATES _state; 
    std::vector<int> _CPUBursts;
    std::vector<int> _IOBursts;
    std::vector<int> _CPUQuantumVec;
    int _agingIndex;
    
	/* Constants */
    static const float INIT_BURST_ESTIMATE; 
};

#endif
