/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 * 
 */

#ifndef SCHEDULER
#define SCHEDULER

#include "Algorithm.hpp"
#include "Utilities.hpp"
#include "Factory.hpp"

class Scheduler {
 public:
	//default constructor
 	Scheduler();

 	void parseTextFile();
 	void welcomeMessage ();
 	void runSpecifiedAlgorithm();
 	std::vector<ProcessControlBlock> getFinalQueueOrder();

 private:
 	Algorithm * _currentAlgorithm;
 	std::vector<ProcessControlBlock> _rawData;
 	Factory _algFactory;
 	std::string _fileStringToOpen;
 	int _intAlgorithmChoice;
 	int _quantumTimeSlice;
 	int _preemption;
 };

#endif
