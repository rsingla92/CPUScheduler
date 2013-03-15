/*
 * EECE 315 - Project 3 CPU Scheduler
 *
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */

#include "Factory.hpp"

/*
 * Function : factory_makeAlgorithm
 * Parameters: name of the Algorithm user wants to create, vector of the input
 *             processes, and time quantum
 * Returns: Pointer to the newly created child object
 * Purpose: To abstract the creation of the different Algorithm objects
 */

Algorithm* Factory::factory_makeAlgorithm(std::string algorithmType, std::vector<ProcessControlBlock> rawData, int timeQuantum) {
    if (rawData.size() > 0 && isAlgorithmType(algorithmType)){
        if (algorithmType == "FCFS")
            return new FirstComeFirstServe(rawData, std::numeric_limits<int>::max()); // effectively infinite quantum time
        else if (algorithmType == "RR")
            return new FirstComeFirstServe(rawData, timeQuantum);
        else if (algorithmType == "TSP")
            return new TimeSlicePriority(rawData, timeQuantum);
        else if (algorithmType == "INSTP")
            return new InstantPriority(rawData, timeQuantum);
        else if (algorithmType == "NPP")
            return new NonPreemptivePriority(rawData, timeQuantum);
        else if (algorithmType == "PSJF")
            return new PreShortestJobFirst(rawData, timeQuantum);
        // this is assuming SJF implements instantaneous preemption
        // otherwise lets process go until completion
        else if (algorithmType == "SPB")
            return new ShortestPreviousBursts(rawData, timeQuantum);
        else if (algorithmType == "PSPB")
                    //return new PreShortestPreviousBursts(rawData, timeQuantum);
        			std::cout << "This doesnt do anything yet... for PSPB";
        else if (algorithmType == "NPSJF")
            return new NonPreShortestJobFirst(rawData, timeQuantum);
        // same assumptions as above
    }
    else {
        std::cout << "Invalid Parameters: now implementing FCFS Alg" << std::endl;
        return new FirstComeFirstServe(rawData, -1);
    }
}
