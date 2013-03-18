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
    int nonExecutingTime;
    int totalBurstTime;
} times;

typedef std::map<int,times> timeMap;
typedef std::map<int,times>::iterator map_itr;

Gantt::Gantt( std::vector<AlgorithmData> queue) : _queue(queue) {}

void Gantt::display()
{
   std::string chart = "| ";
   itr it = _queue.begin();
   int incrementalBurst = 0;

   for(it = _queue.begin() ; it != _queue.end(); ++it) {
       incrementalBurst = it->burstTime;

        while( it->PID == (it+1)->PID) {
           incrementalBurst += it->burstTime;
           ++it;
     }

       if( it->PID == IDLE) {
           chart += "IDLE: " + intToString(it->burstTime)+ " | ";
       } else {
           chart += "PID " + intToString(it->PID) + ": " + intToString(incrementalBurst) + " | ";
       }
   }

    std::cout << chart << std::endl << std::endl;
}

void Gantt::metrics()
{
   timeMap pidTimes;
   int totalBurstTime = 0;
   int totalWaitTime = 0;
   int totalProcesses = 0;
   int totalTurnaround = 0;

   for(itr it =_queue.begin(); it != _queue.end(); ++it) {
       pidTimes[it->PID].waitTime = it->waitTime;
       pidTimes[it->PID].ioTime = it->IOTime;
       pidTimes[it->PID].nonExecutingTime = it->IOTime + it->waitTime;
       pidTimes[it->PID].totalBurstTime += it->burstTime;
       totalBurstTime += it->burstTime;
   }

   // if there was an IDLE placeholder, ignore it.
   totalProcesses = (pidTimes.find(-1)  != pidTimes.end()) ? pidTimes.size()-1 : pidTimes.size();
    
   for(map_itr index = pidTimes.begin(); index != pidTimes.end(); ++index) {
       if(index->first == -1) {
           continue;
       } else {
           std::cout << "PID " << index->first << " - Turnaround time: " << (index->second.nonExecutingTime + index->second.totalBurstTime) << " \t Waiting Time: " << index->second.waitTime << std::endl;
           totalWaitTime += index->second.waitTime;
           totalTurnaround += index->second.nonExecutingTime + index->second.totalBurstTime;
       } 
   }

   std::cout << "The total waiting time was " << totalWaitTime << std::endl;
   std::cout << "The total CPU execution time was " << totalBurstTime << std::endl;
   std::cout << "The number of processes executed was " << totalProcesses << std::endl;
   std::cout << "The throughput of this run per one time unit was " << (float) totalProcesses/totalBurstTime << std::endl;
   std::cout << "The average waiting time per process was " << (float) totalWaitTime/totalProcesses << std::endl;
   std::cout << "the average turnaround time per process was " << (float) totalTurnaround/totalProcesses << std::endl;
   return;
}

std::vector<AlgorithmData> Gantt::getQueue()
{
   return _queue;
}
