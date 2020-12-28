
CC = g++
CXXFLAGS = -O3 -fopt-info -fopenmp -march=native -std=c++17

tsp: Driver.o City.o Naive.o Common.o Distance.o Interface.o Utilities.o Operation.o Pherormone.o Validation.o
	$(CC) $(CXXFLAGS) -o tsp Driver.o City.o Naive.o Common.o Distance.o Interface.o Utilities.o Operation.o Pherormone.o Validation.o

Driver.o: Driver.cpp Driver.h City.h Naive.h Common.h Colonize.h Distance.h Interface.h Utilities.h Operation.h Pherormone.h Validation.h
	$(CC) $(CXXFLAGS) -c Driver.cpp

City.o: City.h Common.h
Colonize.o: Colonize.h Common.h Naive.h Distance.h Operation.h
Common.o: Common.h
Distance.o: Distance.h Distance.h
Interface.o: Interface.h Common.h
Naive.o: Naive.h Common.h Operation.h
Operation.o: Operation.h Common.h
Pherormone.o: Pherormone.h Common.h
Utilities.o: Utilities.h Common.h Distance.h Colonize.h Interface.h Pherormone.h Validation.h
Validation.o: Validation.h Common.h
