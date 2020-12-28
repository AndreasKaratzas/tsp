
CC = g++
CXXFLAGS = -O3 -fopenmp -march=native -std=c++17

tsp: Driver.o
	$(CC) $(CXXFLAGS) -o tsp Driver.o

Driver.o: Driver.cpp Common.h Driver.h City.h Naive.h Common.h Colonize.h Distance.h Interface.h Utilities.h Operation.h Pherormone.h Validation.h
	$(CC) $(CXXFLAGS) -c Driver.cpp

City.o: City.cpp City.h Common.h
	$(CC) $(CXXFLAGS) -c City.cpp

Distance.o: Distance.cpp Distance.h Common.h
	$(CC) $(CXXFLAGS) -c Distance.cpp

Interface.o: Interface.cpp Interface.h Common.h
	$(CC) $(CXXFLAGS) -c Interface.cpp

Operation.o: Operation.cpp Operation.h Common.h
	$(CC) $(CXXFLAGS) -c Operation.cpp

Pherormone.o: Pherormone.cpp Pherormone.h Common.h
	$(CC) $(CXXFLAGS) -c Pherormone.cpp

Validation.o: Validation.cpp Validation.h Common.h
	$(CC) $(CXXFLAGS) -c Validation.cpp

Naive.o: Naive.cpp Naive.h Operation.h Common.h
	$(CC) $(CXXFLAGS) -c Naive.cpp

Colonize.o: Colonize.cpp Colonize.h Common.h Naive.h Distance.h Operation.h
	$(CC) $(CXXFLAGS) -c Colonize.cpp

Utilities.o: Utilities.cpp Utilities.h Common.h Distance.h Colonize.h Interface.h Pherormone.h Validation.h
	$(CC) $(CXXFLAGS) -c Utilities.cpp

clean:
	rm *.o tsp
