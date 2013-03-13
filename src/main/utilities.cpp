/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "utilities.hpp"
#include "TimeSlicePriority.hpp" //temporarily

std::string intToString(const int i) {
   std::stringstream ss;
   ss << i;
   return ss.str();
}

/*
 * Function: isHigherPriority
 * Parameters: The two PCBs to compare (pcb1 and pcb2)
 * Returns: true if pcb1 has a higher priority than pcb2 (low-valued priorities is actually higher priority). 
 * Purpose: This is a predicate used to sort the PCB queues for the Priority algorithms.
 */
bool isHigherPriority( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 ) {
	return (pcb1.getPriority() < pcb2.getPriority()); 
}

bool isLowerTarq( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 ) {
	return (pcb1.getTARQ() < pcb2.getTARQ()); 
}

bool isFirstIOBurstLess( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 ) {
	return (pcb1.getIOBursts().at(0) < pcb2.getIOBursts().at(0));
}
/*
 * Function: arrivesEarlier
 * Parameters: The two PCBs to compare (pcb1 and pcb2)
 * Returns: true if pcb1 has a lower wait time than pcb2. 
 * Purpose: This is a predicate used to sort the PCB queues in the TARQ.
 */
bool arrivesEarlier( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 ) {
	return (pcb1.getTARQ() < pcb2.getTARQ());
}

bool checkToRemoveIO( const ProcessControlBlock& val ) {
	return ( val.getIOBursts().size() == 0 || val.getIOBursts().at(0) <= 0 );
}

bool checkToRemoveTARQ( const ProcessControlBlock& val ) {
	return ( val.getTARQ() <= 0 ); 
}

bool isAlgorithmType (std::string algorithmType){
    if(algorithmType == "FCFS" || algorithmType == "RR" || algorithmType == "NPP" || algorithmType == "TSP" || algorithmType == "INSTP" || algorithmType == "PSJF" || algorithmType == "SPB" || algorithmType == "NPSJF")
        return true;
    else
        return false;
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


void welcomeMessage (int & intAlgorithmChoice, std::string & fileStringToOpen, int & quantumTimeSlice, int & preemption){
	std::cout << "Please type, including the suffix (.txt,etc), the name of the test file to be used: " ;
	std::cin >> (fileStringToOpen);

	std::ifstream myFile(fileStringToOpen.c_str());
	if(myFile.is_open()){
		std::cout << "Your entry, " << fileStringToOpen << ", is valid. loading input file..." << std::endl;
	}
	else{
		fileStringToOpen = "/home/jordenh/Documents/GitHub/CPUScheduler/src/test/process.txt"; //set this line specific to each persons computer
		std::ifstream myFile(fileStringToOpen.c_str());

		if(myFile.is_open()){
			std::cout << "Your entry was invalid, defaulting to default txt file" << std::endl;
		}
		else{
			std::cout << "Error, default program failed to load, try again." << std::endl;
		}
	}

	std::cout << "Please choose which algorithm you would like to run \n1)FCFS \n2)RR \n3)SJF \n4)SPB \n5)Priority" << std::endl;
	std::string tempString = "";
	std::getline(std::cin,tempString);
	std::stringstream(tempString) >> intAlgorithmChoice;

	//enforce input Algorithm Choice to be between 1 and 5
	while(intAlgorithmChoice < 1 || intAlgorithmChoice > 5){
		std::cout << "Please input a proper integer choice (1-5): ";
		std::getline(std::cin,tempString);
		std::stringstream(tempString) >> intAlgorithmChoice;
	}

	if(intAlgorithmChoice >= 2 && intAlgorithmChoice <= 5){
		std::cout << "Please enter the quantum timeslice to use: ";
		std::cin >> quantumTimeSlice;

		while(quantumTimeSlice <= 0){
			std::cout << "Please ensure the timeslice is > 0. Re-input: ";
			std::cin >> quantumTimeSlice;
		}

		if(intAlgorithmChoice >= 3){
			std::cout << "Please enter whether or to have preemption in your algorithm choice ('0'=no preemption, otherwise preemption): ";
			std::cin >> preemption;
		}
	}

	return;
}

void runSpecifiedAlgorithm(int & intAlgorithmChoice, std::vector<ProcessControlBlock> & loadFile, int & quantumTimeSlice, int & preemption){
	switch(intAlgorithmChoice){
	case 1 : std::cout << "FCFS Selected to run..." << std::endl;
		//FCFSAlg testFCFSAlg();
		//testFCFSAlg.run();
		break;
	case 2 : std::cout << "RR Selected to run..." << std::endl;
			//RRAlg testRRAlg(quantumTimeSlice);
			//testRRAlg.run();
		break;
	case 3 : std::cout << "SJF Selected to run..." << std::endl;
		if(preemption){
			//SJFAlg testSJFAlg();
			//testSJFAlg.run();
		} else{
			//SJFAlg testSJFAlg();
			//testSJFAlg.run();
		}
		break;
	case 4 : std::cout << "SPB Selected to run..." << std::endl;
		if(preemption){
			//SPBAlg testSPBAlg();
			//testSPBAlg.run();
		} else{
			//SPBAlg testSPBAlg();
			//testSPBAlg.run();
		}
		break;
	case 5 : std::cout << "Priority Selected to run..." << std::endl;
		if(preemption){
			//TimeSlicePriority testAlgo(loadFile, 3);
			//testAlgo.run();
		} else{
			TimeSlicePriority testAlgo(loadFile, quantumTimeSlice);
			testAlgo.run();
		}
		break;
	default :
		std::cout << "Please input a proper algorithm number, from 1-6." << std::endl;
		intAlgorithmChoice = -1;
		break;
	}

	return;
}
