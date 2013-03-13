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
using std::stringstream;

scheduler::scheduler(){
	_currentAlgorithm = NULL;
	_algFactory = Factory();
	_intAlgorithmChoice = -1;
	_quantumTimeSlice = -1;
	_preemption = 0;
	_fileStringToOpen = "";
}

void scheduler::parseTextFile(){
	vector<int> PCB_CPUTimes;
	vector<int> PCB_IOTimes;
	int priority = -1;
	int TARQ = -1;
	int PID = -1;
	int TNCPU = -1;
	int i = 0;
	int temp = 0;
	string line;
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
	        _rawData.push_back(currentProcess);
	    }
	    myfile.close();
	}

	else {
	    cout << "unable to open file" << endl;
    }
	return;
}

void scheduler::welcomeMessage (){
	_fileStringToOpen= "";
	_intAlgorithmChoice = -1;
	_quantumTimeSlice = -1;
	_preemption = 0;
    string tempString = "";

	cout << "Please type, including the suffix (.txt,etc), the name of the test file to be used: " ;
	cin >> (_fileStringToOpen);

	ifstream myFile(_fileStringToOpen.c_str());
	if(myFile.is_open()){
		cout << "Your entry, " << _fileStringToOpen << ", is valid. loading input file..." << endl;
	}
	else{
		_fileStringToOpen = "/Users/laurenfung/lauren/Desktop/proj 3 master/DerivedData/proj 3 master/Build/Products/Debug/process.txt"; //set this line specific to each persons computer
		ifstream myFile(_fileStringToOpen.c_str());

		if(myFile.is_open()){
			cout << "Your entry was invalid, defaulting to default txt file" << endl;
		}
		else{
			cout << "Error, default program failed to load, try again." << endl;
		}
	}

	cout << "Please choose an algorithm to run: \n1)FCFS \n2)RR \n3)SJF \n4)SPB \n5)Priority" << endl;
	getline(cin,tempString);
	stringstream(tempString) >> _intAlgorithmChoice;

	//enforce input Algorithm Choice to be between 1 and 5
	while(_intAlgorithmChoice < 1 || _intAlgorithmChoice > 5){
		cout << "Please input a proper integer choice (1-5): ";
		getline(cin,tempString);
		stringstream(tempString) >> _intAlgorithmChoice;
	}

	if(_intAlgorithmChoice >= 2 && _intAlgorithmChoice <= 5){
		cout << "Please enter the quantum timeslice to use: ";
		getline(cin,tempString);
		stringstream(tempString) >> _quantumTimeSlice;
		while(_quantumTimeSlice <= 0){
			cout << "must input an integer > 0. Re-input: ";
			getline(cin,tempString);
			stringstream(tempString) >> _quantumTimeSlice;
		}

		if(_intAlgorithmChoice == 3 || _intAlgorithmChoice == 4){
			cout << "Please enter whether to have preemption ('1' = with Preemption, otherwise No Preemption): ";
			getline(cin,tempString);
			stringstream(tempString) >> _preemption;
		}
        
        if(_intAlgorithmChoice == 5){
            cout << "Please select which type of preemption to run ('1' = Patient Preemption, '2' = Impatient Preemption, otherwise No Preemption: ";
            getline(cin, tempString);
            stringstream(tempString) >> _preemption;
        }
	}

	return;
}

void scheduler::runSpecifiedAlgorithm(){
	this->parseTextFile();

	switch(_intAlgorithmChoice){
    case 1 :
        cout << "FCFS selected to run..." << endl << endl;
		_currentAlgorithm = _algFactory.factory_makeAlgorithm("FCFS", _rawData, _quantumTimeSlice);
		break;
    case 2 :
        cout << "RR selected to run..." << endl << endl;
		_currentAlgorithm = _algFactory.factory_makeAlgorithm("RR", _rawData, _quantumTimeSlice);
		break;
    case 3 :
        cout << "SJF selected to run ";
		if(_preemption){
            cout << "with preemption..." << endl << endl;
			_currentAlgorithm = _algFactory.factory_makeAlgorithm("PSJF", _rawData, _quantumTimeSlice);
		} else{
            cout << "without preemption..." << endl << endl;
			_currentAlgorithm = _algFactory.factory_makeAlgorithm("NPSJF", _rawData, _quantumTimeSlice);
		}
		break;
    case 4 :
        cout << "SPB selected to run ";
		if(_preemption){
            cout << "with preemption..." << endl << endl;
			_currentAlgorithm = _algFactory.factory_makeAlgorithm("PSPB", _rawData, _quantumTimeSlice);
		} else{
            cout << "without preemption..." << endl << endl;
			_currentAlgorithm = _algFactory.factory_makeAlgorithm("SPB", _rawData, _quantumTimeSlice);
		}
		break;
	case 5 :
        cout << "Priority selected to run ";
		if(_preemption == 1){
            cout << "with patient preemption..." << endl << endl;
			_currentAlgorithm = _algFactory.factory_makeAlgorithm("TSP", _rawData, _quantumTimeSlice);
		}
        else if(_preemption == 2){
            cout << "wit impatient premption..." << endl << endl;
				_currentAlgorithm = _algFactory.factory_makeAlgorithm("INSTP", _rawData, _quantumTimeSlice);
        }
        else{
            cout << "without preemption..." << endl << endl;
            _currentAlgorithm = _algFactory.factory_makeAlgorithm("NPP", _rawData, _quantumTimeSlice);
			}
		break;
	default :
		cout << "Please input a proper algorithm number (must be between 1 and 5)." << endl;
		_intAlgorithmChoice = -1;
		break;
	}
	_currentAlgorithm->run();

	return;
}

vector<ProcessControlBlock> scheduler::getFinalQueueOrder(){
	if(_currentAlgorithm != NULL){
		return _currentAlgorithm->getFinalQueueOrder();
	}

	return _rawData;
}
