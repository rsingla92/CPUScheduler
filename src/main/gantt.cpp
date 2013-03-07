/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "gantt.h"

Gantt::Gantt( std::vector<ProcessControlBlock> queue) : _queue(queue) {}

void Gantt::display()
{
    std::vector<ProcessControlBlock>::iterator it = getQueue().begin();

    std::string chart = "| "
    for( ; it != getQueue.end(); ++it) {
	chart += itoa(it->getPID()) + " |"; 
    }

   std::cout << chart << endl;
}

std::vector<ProcessControlBlock> Gantt::getQueue()
{
   return _queue;
}
