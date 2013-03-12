/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "scheduler.hpp"
#include "processcontrolblock.hpp"
#include "gantt.hpp"
#include <fstream>
#include "TimeSlicePriority.hpp"


/* Function declarations */
std::vector<ProcessControlBlock> parseTextFile(std::string filename);
void welcomeMessage (int * intAlgorithmChoice, std::string * fileStringToOpen, int * quantumTimeSlice, int * preemption);
void runSpecifiedAlgorithm(int * intAlgorithmChoice, std::vector<ProcessControlBlock> * loadFile, int * quantumTimeSlice, int * preemption);

int main(int argc, char* argv[]){
    std::string contSimulating = "y";
    int intAlgorithmChoice = -1;
    int quantumTimeSlice = -1;
    int preemption = 0;
    std::string fileStringToOpen;
    
    while(contSimulating == "y" && argc == 1){
		welcomeMessage(&intAlgorithmChoice, &fileStringToOpen, &quantumTimeSlice, &preemption);

		std::vector<ProcessControlBlock> loadFile;
		loadFile = parseTextFile(fileStringToOpen);

		runSpecifiedAlgorithm(&intAlgorithmChoice, &loadFile, &quantumTimeSlice, &preemption);

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

    	runSpecifiedAlgorithm(&intAlgorithmChoice, &loadFile, &quantumTimeSlice, &preemption);
    }
    std::cout << "Program Completed." << std::endl;



    /* for testing purposes - you guys can delete this
     int i;
     std::cout <<"this first PID: "  << loadFile[0].getPID() << std::endl;
     std::cout <<"the TARQ: " << loadFile[0].getTARQ() << std::endl;
     std::cout << "the Priority: " << loadFile[0].getPriority() << std::endl;
     std::cout <<"the TNCPU: " << loadFile[0].getTNCPU() << std::endl;
     for (i=0; i<loadFile[0].getCPUBursts().size(); i++)
     std::cout <<"the cpubursts: " << loadFile[0].getCPUBursts()[i] << std:: endl;
     for (i=0; i<loadFile[0].getIOBursts().size(); i++)
     std:: cout<< "the IO: " << loadFile[0].getIOBursts()[i] << std:: endl;
     
     std::cout <<"the second PID: " << loadFile[1].getPID() << std::endl;
     */
    //   welcome();
    //   cpuScheduler = new Scheduler(();
    //   cpuScheduler.run();
    //   gantt = new Gantt();
    //   gantt.chart();
    //   gantt.metrics();
    
    return 0;
}

std::vector<ProcessControlBlock> parseTextFile(std::string filename) {
    std::vector<int> PCB_CPUTimes;
    std::vector<int> PCB_IOTimes;
    int priority = -1;
    int TARQ = -1;
    int PID = -1;
    int TNCPU = -1;
    int i = 0;
    int temp = 0;
    std::string line;
    std::vector<ProcessControlBlock> rawData;
    ProcessControlBlock currentProcess;
    
    //std::ifstream myfile ("/home/jordenh/Documents/GitHub/CPUScheduler/src/test/process.txt");
    std::ifstream myfile (filename.c_str());
    if (myfile.is_open())
    {
        getline(myfile,line); // the first column name line, dont need it
        while (myfile.good())
        {
            // clearing both vectors so each PCB is populated with one line from the text file
            PCB_IOTimes.clear();
            PCB_CPUTimes.clear();
            
            myfile >> PID;
            
            myfile >> TARQ;
            
            myfile >> priority;
            
            myfile >> TNCPU;
            
            for (i = 0; i < (TNCPU-1); i++) { // need last burst to be CPU burst
                myfile >> temp;
                PCB_CPUTimes.push_back(temp);
                
                myfile >> temp;
                PCB_IOTimes.push_back(temp);
            }
            myfile >> temp;
            PCB_CPUTimes.push_back(temp);
            
            currentProcess = ProcessControlBlock(PID, TARQ, priority, TNCPU, PCB_CPUTimes, PCB_IOTimes);
            rawData.push_back(currentProcess);
        }
        myfile.close();
    }
    
    else
        std::cout << "unable to open file" << std::endl;
    
    return rawData;
}


void welcomeMessage (int * intAlgorithmChoice, std::string * fileStringToOpen, int * quantumTimeSlice, int * preemption){
	std::cout << "Please type, including the suffix (.txt,etc), the name of the test file to be used: " ;
	std::cin >> (*fileStringToOpen);

	std::ifstream myFile(fileStringToOpen->c_str());
	if(myFile.is_open()){
		std::cout << "Your entry, " << *fileStringToOpen << ", is valid. loading input file..." << std::endl;
	}
	else{
		*fileStringToOpen = "/home/jordenh/Documents/GitHub/CPUScheduler/src/test/process.txt";
		std::ifstream myFile(fileStringToOpen->c_str());
		if(myFile.is_open())
			std::cout << "Your entry was invalid, defaulting to default txt file" << std::endl;
		else{
			std::cout << "Error, default program failed to load, try again." << std::endl;
		}
	}

	std::cout << "Please choose which algorithm you would like to run \n1)FCFS \n2)RR \n3)SJF \n4)SPB \n5)Priority" << std::endl;
	std::cin >> *intAlgorithmChoice;

	if(*intAlgorithmChoice > 1 && *intAlgorithmChoice <= 5){
		std::cout << "Please enter the quantum timeslice to use: ";
		std::cin >> *quantumTimeSlice;
		while(*quantumTimeSlice <= 0){
			std::cout << "Please ensure the timeslice is > 0. Re-input: ";
			std::cin >> *quantumTimeSlice;
		}

		if(*intAlgorithmChoice >= 3){
			std::cout << "Please enter whether or to have preemption in your algorithm choice ('0'=no preemption, otherwise preemption): ";
			std::cin >> *preemption;
		}
	}

	return;
}

void runSpecifiedAlgorithm(int * intAlgorithmChoice, std::vector<ProcessControlBlock> * loadFile, int * quantumTimeSlice, int * preemption){

	switch(*intAlgorithmChoice){
	case 1 : std::cout << "FCFS Selected to run..." << std::endl;
		//FCFSAlg testFCFSAlg();
		//testFCFSAlg.run();
		break;
	case 2 : std::cout << "RR Selected to run..." << std::endl;
			//RRAlg testRRAlg(quantumTimeSlice);
			//testRRAlg.run();
		break;
	case 3 : std::cout << "SJF Selected to run..." << std::endl;
		if(*preemption){
			//SJFAlg testSJFAlg();
			//testSJFAlg.run();
		} else{
			//SJFAlg testSJFAlg();
			//testSJFAlg.run();
		}
		break;
	case 4 : std::cout << "SPB Selected to run..." << std::endl;
		if(*preemption){
			//SPBAlg testSPBAlg();
			//testSPBAlg.run();
		} else{
			//SPBAlg testSPBAlg();
			//testSPBAlg.run();
		}
		break;
	case 5 : std::cout << "Priority Selected to run..." << std::endl;
		if(*preemption){
			//TimeSlicePriority testAlgo(loadFile, 3);
			//testAlgo.run();
		} else{
			TimeSlicePriority testAlgo(*loadFile, *quantumTimeSlice);
			testAlgo.run();
		}
		break;
	default :
		std::cout << "Please input a proper algorithm number, from 1-6." << std::endl;
		*intAlgorithmChoice = -1;
		break;
	}

	return;
}

