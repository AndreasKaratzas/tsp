
CC = g++
CXXFLAGS = -O3 -fopenmp -march=native -std=c++17

tsp: Driver.o City.o Naive.o Distance.o Interface.o Utilities.o Operation.o Pherormone.o Validation.o Common.o
	$(CC) $(CXXFLAGS) -o tsp Driver.o City.o Naive.o Distance.o Interface.o Utilities.o Operation.o Pherormone.o Validation.o Common.o

Driver.o: Driver.cpp Common.h Driver.h City.h Naive.h Common.h Colonize.h Distance.h Interface.h Utilities.h Operation.h Pherormone.h Validation.h
	$(CC) $(CXXFLAGS) -c Driver.cpp


City.o: City.h Common.h
Distance.o: Distance.h Common.h
Interface.o: Interface.h Common.h
Operation.o: Operation.h Common.h
Pherormone.o: Pherormone.h Common.h
Validation.o: Validation.h Common.h
Naive.o: Naive.h Common.h Operation.h
Colonize.o: Colonize.h Common.h Naive.h Distance.h Operation.h
Utilities.o: Utilities.h Common.h Distance.h Colonize.h Interface.h Pherormone.h Validation.h
Common.o: Common.h
