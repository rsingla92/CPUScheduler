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
