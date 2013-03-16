/*
 * EECE 315 - Project 3 CPU Scheduler
 * 
 * Authors : Lauren Fung, Jorden Hetherington
 *           Jeremy Lord, Rohit Singla
 * 
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <sstream>
#include <iostream>
#include <string>
#include "ProcessControlBlock.hpp"
#include <fstream>

std::string intToString(const int i);
bool isHigherPriority( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 ); 
bool arrivesEarlier( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 ); 
bool checkToRemoveTARQ( const ProcessControlBlock& val );
bool checkToRemoveIO( const ProcessControlBlock& val );
bool isLowerTarq( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 );
bool isFirstIOBurstLess( const ProcessControlBlock& pcb1, const ProcessControlBlock& pcb2 );
bool checkToRemoveWaiting( const ProcessControlBlock& pcb1 ); 
bool isAlgorithmType (std::string algorithmType);
bool isShorterCPUBurst(const ProcessControlBlock& lhs, const ProcessControlBlock& rhs);

#endif
