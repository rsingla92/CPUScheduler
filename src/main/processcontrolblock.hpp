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

class ProcessControlBlock
{

    public:
    ProcessControlBlock();
    ProcessControlBlock(int PID, int TARQ, int PRIO, int TNCPU,
                            std::vector<int> CPUBursts, std::vector<int>IOBursts);
    
    ProcessControlBlock& operator=(const ProcessControlBlock& otherProcess);
    
    int getPID();
    void setPID(int PID);
    
    int getTARQ();
    void setTARQ(int TARQ);
    
    int getPriority();
    void setPriority(int PRIO);
    
    int getTNCPU();
    void setTNCPU(int TNCPU);
    
    std::vector<int> getCPUBursts();
    void setCPUBursts(std::vector<int> CPUBursts);

    std::vector<int> getIOBursts();
    void setIOBursts(std::vector<int> IOBursts);
   
    std::vector<int> getCPUQuantumVec();
    void setCPUQuantumVec(std::vector<int> CPUQuantumVec);
   
    private:
    int _pid;
    int _tarq;
    int _prio;
    int _tncpu;
    std::vector<int> _CPUBursts;
    std::vector<int> _IOBursts;
   
    std::vector<int> _CPUQuantumVec;
};

#endif
