CPUScheduler
============

// EECE 315 2013W
// The University of British Columbia
// Developers:
// Lauren Fung
// Jorden Hetherington
// Jeremy Lord
// Rohit Singla

CPU Scheduler Simulator

As part of an Operating and File Systems course, a simulation for a CPU scheduler has been designed.
Given a .txt file in the following form:
PID TARQ  PRIO  TNCPU CPU1  IO1 CPU2  IO2 CPU3.... 
5   3     2     .....
2   0     7     ......
7   1     1     .......

Where each row is a process, and each column is information pertaining to that process, the simulator can run a any of the following:
//First Come First Serve
//Round Robin with variable time quantum
//Impolite Preemptive Priority
//Patient Preemptive Priority
//Non-preemptive Priority
//Preemptive Shortest Job First 
//Non-preemptive Shortest Job First
//Shortest Previous Burst

The Gantt chart for the specfied algorithm is displayed, along with the metrics pertaining to the resulting run.
Developed in C++. 
