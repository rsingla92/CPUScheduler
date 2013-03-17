/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "Gantt.hpp"

typedef std::vector<AlgorithmData>::iterator itr;

typedef struct {
    int ioTime;
    int waitTime;
    int turnAroundTime;
} times;

typedef std::map<int,times> timeMap;

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
   timeMap pidTimes;
   int totalBurstTime = 0;
   int totalProcesses = 0;

   for(itr it =_queue.begin(); it != _queue.end(); ++it) {
       pidTimes[it->PID].waitTime = it->waitTime;
       pidTimes[it->PID].ioTime = it->IOTime;
       pidTimes[it->PID].turnAroundTime = (it->burstTime + it->IOTime + it->waitTime);
       totalBurstTime += it->burstTime;
   }

   // if there was an IDLE placeholder, ignore it.
   totalProcesses = (pidTimes.find(-1)  != pidTimes.end()) ? pidTimes.size()-1 : pidTimes.size();

   typedef std::map<int,times>::iterator map_itr;

   for(map_itr index = pidTimes.begin(); index != pidTimes.end(); ++index) {
       if(index->first == -1) {
           continue;
       } else {
           std::cout << "PID " << index->first << " turnAroundTime time " << index->second.turnAroundTime << std::endl;
       } 
   }

   std::cout << "The total CPU execution time was " << totalBurstTime << std::endl;
   std::cout << "The number of processes executed was " << totalProcesses << std::endl;
   std::cout << "The throughput of this run per one time unit was " << (float) totalProcesses/totalBurstTime << std::endl;
   return;
}

std::vector<AlgorithmData> Gantt::getQueue()
{
   return _queue;
}
