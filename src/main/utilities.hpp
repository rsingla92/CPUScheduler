/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 * 
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <sstream>
#include <iostream>
#include <string>

std::string intToString(const int i);

std::bool priorityLowToHigh(ProcessControlBlock PCB1, ProcessControlBlock PCB2);


#endif
