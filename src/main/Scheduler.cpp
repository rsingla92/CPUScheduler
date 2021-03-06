/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "Scheduler.hpp"
#include <sstream>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::stringstream;


Scheduler::Scheduler(){
    _currentAlgorithm = NULL;
    _algFactory = Factory();
    _intAlgorithmChoice = -1;
    _quantumTimeSlice = -1;
    _preemption = 0;
    _fileStringToOpen = "";
    _aging = false;
}

Scheduler::~Scheduler(){
    delete _currentAlgorithm;
    _currentAlgorithm = NULL;
}

void Scheduler::parseTextFile(){
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
    if (myfile.is_open()) {
        while (myfile.good()) {
            stringstream ss; 
            getline( myfile, line ); 

            ss.str( line ); 

            PCB_IOTimes.clear();
            PCB_CPUTimes.clear();

            ss >> PID;

            ss >> TARQ;

            ss >> priority;

            ss >> TNCPU;

            for (i = 0; i < (TNCPU-1); i++) { // need last burst to be CPU burst
                ss >> temp;
                PCB_CPUTimes.push_back(temp);

                ss >> temp;
                PCB_IOTimes.push_back(temp);

                if( ss.fail() ) break; 
            }

            ss >> temp;
            PCB_CPUTimes.push_back(temp);

            if( !ss.fail() ) {
                currentProcess = ProcessControlBlock(PID, TARQ, priority, TNCPU, PCB_CPUTimes, PCB_IOTimes);
                _rawData.push_back(currentProcess);
            } 
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
    return;
}

void Scheduler::welcomeMessage (){
    _fileStringToOpen= "";
    _intAlgorithmChoice = -1;
    _quantumTimeSlice = -1;
    _preemption = 0;
    _aging = false;
    string tempString = "";

    ifstream myFile(_fileStringToOpen.c_str());

    while(myFile.fail()) {
        cout << "Please type, including the suffix (.txt,etc), the name of the test file to be used: " ;
        getline(cin, _fileStringToOpen);
        ifstream myFile(_fileStringToOpen.c_str());
        if(myFile.is_open()) {
            cout << "Your entry, " << _fileStringToOpen << ", is valid." << endl << "loading input file..." << endl << endl;
            break;
        } else {
        cout << "Your entry, " << _fileStringToOpen << ", is not valid." << endl;
        }
    }

    cout << "Please choose an algorithm to run: \n1)FCFS \n2)RR \n3)SJF \n4)SPB \n5)Priority" << endl << endl;
    cout << "Selection: ";
    getline(cin,tempString);
    stringstream(tempString) >> _intAlgorithmChoice;

    //enforce input Algorithm Choice to be between 1 and 5
    while(_intAlgorithmChoice < 1 || _intAlgorithmChoice > 5){
        cout << "Please input a proper integer choice (1-5): ";
        getline(cin,tempString);
        stringstream(tempString) >> _intAlgorithmChoice;
    }

    if( _intAlgorithmChoice > 2 ) {
        cout << "Would you like to implement aging? (enter '1' = Aging, otherwise No Aging): ";
        getline(cin, tempString);
        if(tempString == "1")
            _aging = true;
        else
            _aging = false;
    }

    if(_intAlgorithmChoice == 2 || _intAlgorithmChoice == 5) {
        if (_intAlgorithmChoice == 5) {
            cout << "Please select which type of preemption to run ('1' = Patient Preemption, '2' = Impatient Preemption, otherwise No Preemption): ";
            getline(cin, tempString);
            stringstream(tempString) >> _preemption;
        }
        if (_preemption == 1 || _intAlgorithmChoice == 2){
            cout << "Please enter the quantum timeslice to use: ";
            getline(cin,tempString);
            stringstream(tempString) >> _quantumTimeSlice;
            while(_quantumTimeSlice <= 0) {
                cout << "Must input an integer > 0. Re-input: ";
                getline(cin,tempString);
                stringstream(tempString) >> _quantumTimeSlice;
            }
        }
    }
    
    else if( _intAlgorithmChoice == 3 || _intAlgorithmChoice == 4 ) {
        cout << "Please enter whether to have preemption ('1' = with Preemption, otherwise No Preemption): ";
        getline(cin,tempString);
        stringstream(tempString) >> _preemption;

        if( _intAlgorithmChoice == 4 ) {
            cout << "Please enter your alpha-value (between 0 and 1): ";
            getline(cin, tempString);
            stringstream(tempString) >> _alpha;
            while( _alpha < 0.0 || _alpha > 1.0 ) {
                cout << "Must input a value in the range 0 to 1. Re-input: ";
                getline(cin, tempString);
                stringstream(tempString) >> _alpha;
            }
        }
    }

    return;
}

void Scheduler::runSpecifiedAlgorithm(){
    this->parseTextFile();
    delete this->_currentAlgorithm;
    this->_currentAlgorithm = NULL;
    cout << endl;
    
    switch(_intAlgorithmChoice){
    case 1 :
            cout << "FCFS selected to run..." << endl;
            _currentAlgorithm = _algFactory.factory_makeAlgorithm("FCFS", _rawData, _quantumTimeSlice);
            break;
    case 2 :
            cout << "RR selected to run..." << endl;
            _currentAlgorithm = _algFactory.factory_makeAlgorithm("RR", _rawData, _quantumTimeSlice);
            break;
    case 3 :
            cout << "SJF selected to run ";
            if(_preemption == 1){
                cout << "with preemption..." << endl;
                _currentAlgorithm = _algFactory.factory_makeAlgorithm("PSJF", _rawData, _quantumTimeSlice, _aging);
            } else{
                cout << "without preemption..." << endl;
                _currentAlgorithm = _algFactory.factory_makeAlgorithm("NPSJF", _rawData, _quantumTimeSlice, _aging);
            }
            break;
    case 4 :
            cout << "SPB selected to run ";
            if(_preemption == 1){
                cout << "with preemption..." << endl;
                _currentAlgorithm = _algFactory.factory_makeAlgorithm("PSPB", _rawData, _quantumTimeSlice, _aging, _alpha);
            }
            else{
                cout << "without preemption..." << endl;
                _currentAlgorithm = _algFactory.factory_makeAlgorithm("SPB", _rawData, _quantumTimeSlice, _aging, _alpha);
            }
            break;
    case 5 :
            cout << "Priority selected to run ";
            if(_preemption == 1){
                cout << "with patient preemption..." << endl;
                _currentAlgorithm = _algFactory.factory_makeAlgorithm("TSP", _rawData, _quantumTimeSlice, _aging);
            }
            else if(_preemption == 2){
                cout << "with impatient premption..." << endl;
                _currentAlgorithm = _algFactory.factory_makeAlgorithm("INSTP", _rawData, _quantumTimeSlice, _aging);
            }
            else{
                cout << "without preemption..." << endl;
                _currentAlgorithm = _algFactory.factory_makeAlgorithm("NPP", _rawData, _quantumTimeSlice, _aging);
            }
            break;
    default :
            cout << "Please input a proper algorithm number (must be between 1 and 5)." << endl;
            _intAlgorithmChoice = -1;
            break;
    }
    if(_aging)
        cout << "Aging enabled" << endl << endl;
    else
        cout << "Aging not enabled" << endl << endl;
    _currentAlgorithm->run();
    _rawData.clear();
    return;
}

vector<AlgorithmData> Scheduler::getFinalQueueOrder(){
    return _currentAlgorithm->getFinalQueueOrder();
}
