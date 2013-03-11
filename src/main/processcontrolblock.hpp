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
    
    int getPID() const;
    void setPID(int PID);
    
    int getTARQ() const;
    void setTARQ(int TARQ);
    
    int getPriority() const;
    void setPriority(int PRIO);
    
    int getTNCPU() const;
    void setTNCPU(int TNCPU);
    
    std::vector<int> getCPUBursts() const;
    void setCPUBursts(std::vector<int> CPUBursts);

    std::vector<int> getIOBursts() const;
    void setIOBursts(std::vector<int> IOBursts);
   
   int getArrivalTime();
   void setArrivalTime(int arrivalTime);
   private:
   int _pid;
   int _arrivalTime;
   std::vector<int> _CPUBursts;
   std::vector<int> _IOBursts;
    std::vector<int> getCPUQuantumVec() const;
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
