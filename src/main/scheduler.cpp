/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
 
#include "scheduler.hpp"

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

scheduler::scheduler(){
	_currentAlgorithm = NULL;
	_algFactory = new Factory();
	_intAlgorithmChoice = -1;
	_quantumTimeSlice = -1;
	_preemption = 0;
	_fileStringToOpen = "";
}

void scheduler::parseTextFile(){
	std::vector<int> PCB_CPUTimes;
	std::vector<int> PCB_IOTimes;
	int priority = -1;
	int TARQ = -1;
	int PID = -1;
	int TNCPU = -1;
	int i = 0;
	int temp = 0;
	string line;
	vector<ProcessControlBlock> rawData;
	ProcessControlBlock currentProcess;

	ifstream myfile (_fileStringToOpen.c_str());
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

	_rawData = rawData;
	return;
}

void scheduler::welcomeMessage (){
	cout << "Please type, including the suffix (.txt,etc), the name of the test file to be used: " ;
	cin >> (_fileStringToOpen);

	ifstream myFile(_fileStringToOpen.c_str());
	if(myFile.is_open()){
		cout << "Your entry, " << _fileStringToOpen << ", is valid. loading input file..." << std::endl;
	}
	else{
		_fileStringToOpen = "/home/jordenh/Documents/GitHub/CPUScheduler/src/test/process.txt"; //set this line specific to each persons computer
		ifstream myFile(_fileStringToOpen.c_str());

		if(myFile.is_open()){
			cout << "Your entry was invalid, defaulting to default txt file" << std::endl;
		}
		else{
			cout << "Error, default program failed to load, try again." << std::endl;
		}
	}

	cout << "Please choose which algorithm you would like to run \n1)FCFS \n2)RR \n3)SJF \n4)SPB \n5)Priority" << std::endl;
	string tempString = "";
	getline(std::cin,tempString);
	stringstream(tempString) >> _intAlgorithmChoice;

	//enforce input Algorithm Choice to be between 1 and 5
	while(_intAlgorithmChoice < 1 || _intAlgorithmChoice > 5){
		cout << "Please input a proper integer choice (1-5): ";
		getline(cin,tempString);
		stringstream(tempString) >> _intAlgorithmChoice;
	}

	if(_intAlgorithmChoice >= 2 && _intAlgorithmChoice <= 5){
		cout << "Please enter the quantum timeslice to use: ";
		cin >> _quantumTimeSlice;

		while(_quantumTimeSlice <= 0){
			cout << "Please ensure the timeslice is > 0. Re-input: ";
			cin >> _quantumTimeSlice;
		}

		if(_intAlgorithmChoice >= 3){
			cout << "Please enter whether or to have preemption in your algorithm choice ('0'=no preemption, otherwise preemption): ";
			cin >> _preemption;
		}
	}

	return;
}

void scheduler::runSpecifiedAlgorithm(){



	switch(_intAlgorithmChoice){
	case 1 : cout << "FCFS Selected to run..." << endl;
		//FCFSAlg testFCFSAlg();
		//testFCFSAlg.run();
		break;
	case 2 : cout << "RR Selected to run..." << endl;
			//RRAlg testRRAlg(quantumTimeSlice);
			//testRRAlg.run();
		break;
	case 3 : cout << "SJF Selected to run..." << endl;
		if(_preemption){
			//SJFAlg testSJFAlg();
			//testSJFAlg.run();
		} else{
			//SJFAlg testSJFAlg();
			//testSJFAlg.run();
		}
		break;
	case 4 : cout << "SPB Selected to run..." << endl;
		if(_preemption){
			//SPBAlg testSPBAlg();
			//testSPBAlg.run();
		} else{
			//SPBAlg testSPBAlg();
			//testSPBAlg.run();
		}
		break;
	case 5 : cout << "Priority Selected to run..." << endl;
		if(_preemption){
			//TimeSlicePriority testAlgo(loadFile, 3);
			//testAlgo.run();
		} else{
			TimeSlicePriority testAlgo(_rawData, _quantumTimeSlice);
			testAlgo.run();
		}
		break;
	default :
		cout << "Please input a proper algorithm number, from 1-6." << endl;
		_intAlgorithmChoice = -1;
		break;
	}

	return;
}

vector<ProcessControlBlock> scheduler::getFinalQueueOrder(){
	if(_currentAlgorithm != NULL){
		return _currentAlgorithm->getFinalQueueOrder();
	}

	return *(new vector<ProcessControlBlock>());
}
