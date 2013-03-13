/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "scheduler.hpp"
#include "processcontrolblock.hpp"
#include "TimeSlicePriority.hpp"
#include "gantt.hpp"
#include "utilities.hpp"
#include <fstream>

int main(int argc, char* argv[]){
    std::string contSimulating = "y";
    
    scheduler sched = scheduler();

    while(contSimulating == "y" && argc == 1){
    	sched.welcomeMessage();
    	sched.runSpecifiedAlgorithm();

		std::cout << "Do you wish to continue? ('y'/'n') ";
		std::cin >> contSimulating;
    }

    std::cout << "Program Completed." << std::endl;
    
    return 0;
}
