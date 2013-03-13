CC=g++
CFLAGS=-g -Wall 

all: simulator
	
simulator                :  
	$(CC) -o simulator simulator.o Algorithm.o FCFSAlg.o gantt.o processcontrolblock.o scheduler.o TimeSlicePriority.o utilities.o

simulator.o              : simulator.cpp simulator.hpp scheduler.hpp processcontrolblock.hpp gant.hpp
	$(CC) $(CFLAGS) -c simulator.cpp
	
Algorithm.o              : Algorithm.cpp Algorithm.hpp processcontrolblock.hpp utilities.hpp
	$(CC) $(CFLAGS) -c Algorithm.cpp
	
FCFSAlg.o                : FCFSAlg.cpp FCFSAlg.hpp Algorithm.hpp processcontrolblock.hpp utilities.hpp
	$(CC) $(CFLAGS) -c FCFSAlg.cpp
	
gantt.o                  : gantt.cpp gantt.hpp processcontrolblock.hpp utilities.hpp
	$(CC) $(CFLAGS) -c gantt.cpp
	
processcontrolblock.o    : processcontrolblock.cpp processcontrolblock.hpp
	$(CC) $(CFLAGS) -c processcontrolblock.cpp
	
scheduler.o              : scheduler.cpp scheduler.hpp
	$(CC) $(CFLAGS) -c scheduler.cpp
	
TimeSlicePriority.o      : TimeSlicePriority.cpp TimeSlicePriority.hpp Algorithm.hpp
	$(CC) $(CFLAGS) -c TimeSlicePriority.cpp
	
utilities.o              : utilities.cpp utilities.hpp processcontrolblock.hpp
	$(CC) $(CFLAGS) -c utilities.cpp
	
clean:
	rm -f *o simulator
		

