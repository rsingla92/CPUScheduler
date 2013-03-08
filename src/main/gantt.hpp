/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "processcontrolblock.hpp"
#include <sstream>
#include <string>
#include <iostream>

class Gantt
{
   public:
       Gantt( std::vector<ProcessControlBlock> queue );
       void display();
       void metrics();
       std::vector<ProcessControlBlock> getQueue();

   private:
     std::vector<ProcessControlBlock> _queue;
};

std::string intToString(const int& i)
{
   std::stringstream ss;
   ss << i;
   return ss.str();
}
