/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "Scheduler.hpp"
#include "ProcessControlBlock.hpp"
#include "Gantt.hpp"
#include "Utilities.hpp"
#include <fstream>

int main(int argc, char* argv[]){
    std::string contSimulating = "y";
    Scheduler sched = Scheduler();
 
    while(contSimulating == "y" && argc == 1){
    	sched.welcomeMessage();
    	sched.runSpecifiedAlgorithm();

        Gantt gantt = Gantt(sched.getFinalQueueOrder());
        gantt.display();
        gantt.metrics();
        std::cout << std::endl;
        
        do {
		std::cout << "Do you wish to continue? ('y'/'n') ";
		getline(std::cin, contSimulating);
        } while (contSimulating != "y" && contSimulating != "n");
        std::cout << std::endl;
    }

    std::cout << "Program Completed." << std::endl;
    
    return 0;
}
