/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "Gantt.hpp"

typedef std::vector<AlgorithmData>::iterator itr;
typedef std::map<int,int> waitMap;

Gantt::Gantt( std::vector<AlgorithmData> queue) : _queue(queue) {}

void Gantt::display()
{

   std::string chart = "|";
   itr it = _queue.begin();
   
   for( it = _queue.begin(); it != _queue.end(); ++it) {
       int tempTime = 0;
       while(it->PID == (it+1)->PID) {
            tempTime += it->burstTime;
            it++;
       }

       // kk now what.
   }


   for(it = _queue.begin() ; it != _queue.end(); ++it) {
       if( it->PID == IDLE) {
           chart += "IDLE | ";
       } else {
           chart += intToString(it->PID) + " | ";
       }
   }

   std::cout << chart << std::endl;
}

void Gantt::metrics()
{
   waitMap waitTimes;

   for(itr it =_queue.begin(); it != _queue.end(); ++it) {
       waitTimes[it->PID] = it->waitTime;
   }

   return;
}

std::vector<AlgorithmData> Gantt::getQueue()
{
   return _queue;
}
