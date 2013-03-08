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
   int getPID();
   void setPID(int PID);
   
   std::vector<int> getCPUBursts();
   void setCPUBursts(std::vector<int> CPUBursts);
   
   std::vector<int> getIOBursts();
   void setIOBursts(std::vector<int> IOBursts);
   
   std::vector<int> getCPUQuantumVec();
   void setCPUQuantumVec(std::vector<int> CPUQuantumVec);
   
   private:
   int _pid;
   std::vector<int> _CPUBursts;
   std::vector<int> _IOBursts;
   
   std::vector<int> _CPUQuantumVec;
};

#endif
