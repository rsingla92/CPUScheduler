/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
 
#ifndef GANTT_H
#define GANTT_H

#include "Algorithm.hpp"
#include "Utilities.hpp"
#include <string>
#include <iostream>
#include <map>

class Gantt
{
   public:
       Gantt( std::vector<AlgorithmData> queue );
       void display();
       void metrics();
       std::vector<AlgorithmData> getQueue();

   private:
     std::vector<AlgorithmData> _queue;
};


#endif
