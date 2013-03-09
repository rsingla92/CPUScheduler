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
   int getPID() const;
   void setPID(int PID);
   
   std::vector<int> getCPUBursts() const;
   void setCPUBursts(std::vector<int> CPUBursts);
   
   std::vector<int> getIOBursts() const;
   void setIOBursts(std::vector<int> IOBursts);
   
   std::vector<int> getCPUQuantumVec() const;
   void setCPUQuantumVec(std::vector<int> CPUQuantumVec);

   int getTimeOfArrival() const;
   void setTimeOfArrival( int timeOfArrival ); 

   int getPriority() const;
   void setPriority( int priority ); 
   
private:
   int _pid;
   int _timeOfArrival; 
   int _priority; 
   std::vector<int> _CPUBursts;
   std::vector<int> _IOBursts;
   std::vector<int> _CPUQuantumVec;
};

#endif
