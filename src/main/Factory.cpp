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

Algorithm* Factory::factory_makeAlgorithm(std::string algorithmType, std::vector<ProcessControlBlock> rawData, int timeQuantum, float alpha, bool aging) {
    if (rawData.size() > 0 && isAlgorithmType(algorithmType)){
        if (algorithmType == "FCFS")
            return new FirstComeFirstServe(rawData, std::numeric_limits<int>::max()); // effectively infinite quantum time
        else if (algorithmType == "RR")
            return new FirstComeFirstServe(rawData, timeQuantum);
        else if (algorithmType == "TSP")
            return new PatientPriority(rawData, timeQuantum, aging);
        else if (algorithmType == "INSTP")
            return new ImpatientPriority(rawData, timeQuantum, aging);
        else if (algorithmType == "NPP")
            return new NonPreemptivePriority(rawData, timeQuantum, aging);
        else if (algorithmType == "PSJF")
            return new PreemptiveShortestJobFirst(rawData, aging);
        else if (algorithmType == "SPB")
            return new NonPreemptiveShortestPreviousBursts(rawData, aging, alpha);
        else if (algorithmType == "PSPB")
            return new PreemptiveShortestPreviousBursts(rawData, aging, alpha);
        else if (algorithmType == "NPSJF")
            return new NonPreemptiveShortestJobFirst(rawData, aging);
    }

    std::cout << "Invalid Parameters: now implementing First Come First Serve" << std::endl;
    return new FirstComeFirstServe(rawData, std::numeric_limits<int>::max());
}
