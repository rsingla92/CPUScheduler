/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 */
#include "Utilities.hpp"
#include <math.h>

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
    return (pcb1.getPriority() - pcb1.getAgingPriorityOffset() < pcb2.getPriority() - pcb2.getAgingPriorityOffset());
}

bool isLowerTarq( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 ) {
	return (pcb1.getTARQ() < pcb2.getTARQ()); 
}

bool isFirstIOBurstLess( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 ) {
	return (pcb1.getIOBursts().at(0) < pcb2.getIOBursts().at(0));
}

bool checkToRemoveWaiting( const ProcessControlBlock& pcb ) {
	return ( pcb.getState() == READY ); 
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

/* 
 * Function : isAlgorithmType
 * Parameters : a string that contains the initials for an algorithm type
 * Returns : true if the string matches any of the known initials for an algorithm
 * Purpose : to verify that the algorithm to create is known by the Factory
 */

bool isAlgorithmType (std::string algorithmType){
    if(algorithmType == "FCFS" || algorithmType == "RR" || algorithmType == "NPP" || algorithmType == "TSP" || algorithmType == "INSTP" || algorithmType == "PSJF" || algorithmType == "PSPB" || algorithmType == "SPB" || algorithmType == "NPSJF")
        return true;
    else
        return false;
}

/*
 * Function: isShorterCPUBurst
 * Parameters: The two PCBs to compare (lhs and rhs) 
 * Returns: true if the lhs CPUBurst is less than the rhs CPUBurst
 * Purpose: This is a predicate used to sort the PCB queues ShortestJobFirst Algorithm and takes into
 *          account the aging offset for time.
 */

bool isShorterCPUBurst( const ProcessControlBlock& lhs, const ProcessControlBlock& rhs) {
    return (ceil((float)lhs.getCPUBursts().at(0)/lhs.getAgingTimeOffset()) < ceil((float)rhs.getCPUBursts().at(0)/rhs.getAgingTimeOffset()) );
}

/*
 * Function: isShorterPreviousCPUBAvg
 * Parameters: The two PCBs to compare (lhs and rhs)
 * Returns: true if the lhs CPUBurst Average is less than the rhs CPUBurst Average
 * Purpose: This is a predicate used to sort the PCB queues ShortestPreviousBursts Algorithm and 
 *          takes into account the aging offset for time.
 */

bool isShorterPreviousCPUAvg(const ProcessControlBlock& lhs, const ProcessControlBlock& rhs) {
    return( ceil((float)lhs.getBurstAvg()/lhs.getAgingTimeOffset()) < ceil((float)rhs.getBurstAvg()/rhs.getAgingTimeOffset()) );
}
