/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "gantt.hpp"

Gantt::Gantt( std::vector<ProcessControlBlock> queue) : _queue(queue) {}

void Gantt::display()
{

    std::vector<ProcessControlBlock> temp(this->getQueue());
    std::vector<ProcessControlBlock>::iterator it = temp.begin();

    std::string chart = "| ";
    for( ; it != temp.end(); ++it) {
	chart += intToString(it->getPID()) + " |"; 
    }

   std::cout << chart << std::endl;
}

std::vector<ProcessControlBlock> Gantt::getQueue()
{
   return _queue;
}
