#include <vector>
#include <iostream>

class ProcessControlBlock
{

   public:
   int getPID();
   void setPID();

   private:
   int _pid;
   std::vector<int> _CPUBursts;
   std::vector<int> _IOBursts;
   
   std::vector<int> _CPUQuantumVec;
};

