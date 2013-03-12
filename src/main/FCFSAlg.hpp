/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#ifndef FCFSALG_H
#define FCFSALG_H

#include "Algorithm.hpp" 
#include "processcontrolblock.hpp"
#include "utilities.hpp"
#include <assert.h>

class FCFSAlg : public Algorithm {

public:
	FCFSAlg(std::vector<ProcessControlBlock> inputRawData, int quantumTime); 
	
	void run();

private:

};

#endif
