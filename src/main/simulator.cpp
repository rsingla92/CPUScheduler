/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "scheduler.hpp"
#include "processcontrolblock.hpp"
#include "gantt.hpp"
#include "utilities.hpp"
#include <fstream>

int main(int argc, char* argv[]){
    std::string contSimulating = "y";
    int intAlgorithmChoice;
    int quantumTimeSlice;
    int preemption;
    std::string fileStringToOpen;
    
    while(contSimulating == "y" && argc == 1){
    	intAlgorithmChoice = -1;
    	quantumTimeSlice = -1;
    	preemption = 0;
    	fileStringToOpen = "";

		welcomeMessage(intAlgorithmChoice, fileStringToOpen, quantumTimeSlice, preemption);

		std::vector<ProcessControlBlock> loadFile;
		loadFile = parseTextFile(fileStringToOpen);

		runSpecifiedAlgorithm(intAlgorithmChoice, loadFile, quantumTimeSlice, preemption);

		std::cout << "Do you wish to continue? ('y'/'n') ";
		std::cin >> contSimulating;
    }
    if(argc > 1){
    	intAlgorithmChoice = (int)(*argv[1]);
    	if(intAlgorithmChoice >= 2 && argv[2] != NULL){
    		quantumTimeSlice = (int)(*argv[2]);
    	}
    	if(intAlgorithmChoice >= 3 && argv[3] != NULL){
    		preemption = (int)(*argv[3]);
    	}

    	std::vector<ProcessControlBlock> loadFile;
    	loadFile = parseTextFile(fileStringToOpen);

    	runSpecifiedAlgorithm(intAlgorithmChoice, loadFile, quantumTimeSlice, preemption);
    }
    std::cout << "Program Completed." << std::endl;

    //   welcome();
    //   cpuScheduler = new Scheduler(();
    //   cpuScheduler.run();
    //   gantt = new Gantt();
    //   gantt.chart();
    //   gantt.metrics();
    
    return 0;
}
