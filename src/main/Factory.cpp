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

Algorithm* Factory::factory_makeAlgorithm(std::string algorithmType, std::vector<ProcessControlBlock> rawData, int timeQuantum, float alpha) {
    if (rawData.size() > 0 && isAlgorithmType(algorithmType)){
        if (algorithmType == "FCFS")
            return new FirstComeFirstServe(rawData, -1); // -1 for infinite timeQuantum
        else if (algorithmType == "RR")
            return new FirstComeFirstServe(rawData, timeQuantum);
        else if (algorithmType == "TSP")
            return new PatientPriority(rawData, timeQuantum);
        else if (algorithmType == "INSTP")
            return new ImpatientPriority(rawData, timeQuantum);
        else if (algorithmType == "NPP")
            return new NonPreemptivePriority(rawData, timeQuantum);
        else if (algorithmType == "PSJF")
            return new PreemptiveShortestJobFirst(rawData, timeQuantum);
        // this is assuming SJF implements instantaneous preemption
        // otherwise lets process go until completion
        else if (algorithmType == "SPB")
            return new NonPreemptiveShortestPreviousBursts(rawData, alpha);
        else if (algorithmType == "PSPB")
            return new PreemptiveShortestPreviousBursts(rawData, alpha);
        else if (algorithmType == "NPSJF")
            return new NonPreemptiveShortestJobFirst(rawData);
        // same assumptions as above
    }

    std::cout << "Invalid Parameters: now implementing FCFS Alg" << std::endl;
    return new FirstComeFirstServe(rawData, -1);
}
