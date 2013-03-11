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

/* Function declarations */
std::vector<ProcessControlBlock> parseTextFile();

int main(int argc, char* argv[]){
    
    std::vector<ProcessControlBlock> loadFile;
    loadFile = parseTextFile();
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

	return 0;

std::vector<ProcessControlBlock> parseTextFile() {
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
    
    
    std::ifstream myfile ("process.txt");
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
        std::cout << "unable to open file";
    
    return rawData;
}

