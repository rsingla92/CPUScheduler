/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "ProcessControlBlock.h"

class Gantt
{
   public:
       Gantt( std::vector<ProcessControlBlock> queue );
       void display();
       void metrics();
   private:
     std::vector<ProcessControlBlock> queue;
}
