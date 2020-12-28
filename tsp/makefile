
CC = g++
CXXFLAGS = -O3 -fopenmp -march=native -std=c++17

tsp: Driver.o
	$(CC) $(CXXFLAGS) -o tsp Driver.o City.o Naive.o Common.o Colonize.o Distance.o Interface.o Utilities.o Operation.o Pherormone.o Validation.o

Driver.o: Driver.cpp Common.h Driver.h City.h Naive.h Common.h Colonize.h Distance.h Interface.h Utilities.h Operation.h Pherormone.h Validation.h
	$(CC) $(CXXFLAGS) -c Driver.cpp

City.o: City.cpp City.h Common.h
Distance.o: Distance.cpp Distance.h Common.h
Interface.o: Interface.cpp Interface.h Common.h
Operation.o: Operation.cpp Operation.h Common.h
Pherormone.o: Pherormone.cpp Pherormone.h Common.h
Validation.o: Validation.cpp Validation.h Common.h
Naive.o: Naive.cpp Naive.h Operation.h Common.h
Colonize.o: Colonize.cpp Colonize.h Common.h Naive.h Distance.h Operation.h
Utilities.o: Utilities.cpp Utilities.h Common.h Distance.h Colonize.h Interface.h Pherormone.h Validation.h

clean:
	rm *.o tsp
