/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */


#include "utilities.hpp"



std::string intToString(const int i)
{
   std::stringstream ss;
   ss << i;
   return ss.str();
}

std::bool priorityLowToHigh(ProcessControlBlock PCB1, ProcessControlBlock PCB2)
{
	if(PCB1.getPriority() < PCB2.getPriority()) //NEED TO DEFINE THIS VARIABLE AND THE ACCESSOR
	{
		return true;
	}
	else 
		return false;
}
