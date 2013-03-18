OBJS = Algorithm.o Factory.o FirstComeFirstServe.o Gantt.o ImpatientPriority.o NonPreemptivePriority.o \
       NonPreemptiveShortestJobFirst.o NonPreemptiveShortestPreviousBursts.o PatientPriority.o \
       PreemptiveShortestJobFirst.o PreemptiveShortestPreviousBursts.o ProcessControlBlock.o Scheduler.o \
       Simulator.o Utilities.o 
CC = g++
CFLAGS = -O -Wall

CPUScheduler: ${OBJS}
	${CC} -o CPUScheduler ${CFLAGS} ${OBJS}

Algorithm.o: Algorithm.cpp Algorithm.hpp
	${CC} -c ${CFLAGS} $< 

Factory.o: Factory.cpp Factory.hpp
	${CC} -c ${CFLAGS} $< 

Gantt.o: Gantt.cpp Gantt.hpp
	${CC} -c ${CFLAGS} $< 

Scheduler.o: Scheduler.cpp Scheduler.hpp
	${CC} -c ${CFLAGS} $< 

Simulator.o: Simulator.cpp Scheduler.hpp ProcessControlBlock.hpp Gantt.hpp Utilities.hpp
	${CC} -c ${CFLAGS} $< 

Utilities.o: Utilities.cpp Utilities.hpp
	${CC} -c ${CFLAGS} $<

%.o: $*.cpp $*.hpp
	${CC} -c ${CFLAGS} $<

.PHONY: clean

clean:
	rm CPUScheduler ${OBJS}
