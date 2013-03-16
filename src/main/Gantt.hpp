/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
 
#ifndef GANTT_H
#define GANTT_H

#include "processcontrolblock.hpp"
#include "utilities.hpp"
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


#endif
