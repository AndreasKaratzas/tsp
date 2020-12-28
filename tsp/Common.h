/**
 * Common.h
 *
 * In this header file, we define the constants
 * used throughout the project. We also
 * include all the header files necessary to 
 * make the implementation work.
 */

#pragma once

#include <array>                                            /// std::array
#include <cmath>                                            /// std::sqrt
#include <vector>                                           /// std::vector
#include <chrono>                                           /// std::chrono
#include <string>                                           /// std::string
#include <random>                                           /// std::random_device
#include <limits>                                           /// std::numeric_limits
#include <utility>                                          /// std::pair
#include <fstream>                                          /// std::ofstream
#include <numeric>                                          /// std::iota
#include <iomanip>                                          /// std::setw
#include <iostream>                                         /// std::cout
#include <iterator>                                         /// std::<T>::iterator
#include <algorithm>                                        /// std::find
#include <functional>                                       /// std::bind

#include <omp.h>                                            /// OpenMP Multiprocessing Programming Framework


constexpr int TEST_MODE = 1;                                /// If 0 then the algorithm runs in debug mode, 
                                                            /// meaning less `N_POINTS` (cities), iterations 
                                                            /// and more verbosity. If 1 then the algorithm 
                                                            /// runs in release mode.
constexpr int ALGORITHM = 0;                                /// If 0 then the algorithm running is the `Naive TSP`, as described in `Utilities.cpp`
                                                            /// If 1 then the algorithm running is the `Naive TSP` (Parallel Implementation), as described in `Utilities.cpp`
                                                            /// If 2 then the algorithm running is the `TSP with nearest neighbor`, as described in `Utilities.cpp`
                                                            /// If 3 then the algorithm running is the `TSP with naive nearest neighbor`, as described in `Utilities.cpp`
                                                            /// If 4 then the algorithm running is the `TSP with naive nearest neighbor` (Parallel Implementation), as described in `Utilities.cpp`
                                                            /// If 5 then the algorithm running is the `ACS TSP`, as described in `Utilities.cpp`
                                                            /// If 6 then the algorithm running is the `ACS TSP` (Parallel Implementation), as described in `Utilities.cpp`
                                                            /// Else no algorithm runs and a warning is displayed
constexpr int N_THREADS = 12;                               /// This is the number of threads requested in any parallel implementations of the project

constexpr int X_MAX = 1000;                                 /// This is the upper limit of any city's "Longitude". This means that a city can have X coordinates that belong in [0, X_MAX]
constexpr int Y_MAX = 1000;                                 /// This is the upper limit of any city's "Latitude". This means that a city can have Y coordinates that belong in [0, Y_MAX]
constexpr int N_POINTS = (                                  /// This variable sets the number of cities. For the ACS implementations, this number must be low, due to memory management issues.
    TEST_MODE == 1 ? 10   :                                 /// That is mainly due to the pherormone matrix, which is a dense matrix, and cannot be easily factorized to optimize memory management. 
    ALGORITHM == 5 ? 1000 :
    ALGORITHM == 6 ? 1000 : 10000);
constexpr int ITERATIONS = (                                /// This is the number of iterations that any algorithm will execute. The TSP is an NP-complete problem. 
    TEST_MODE == 1 ? 10     :                               /// Therefore and since the approaches in this project are mainly naive (there is a statistical element, 
    ALGORITHM == 1 ? 10000  :                               /// such as a random choice between N possible decisions), we set a number of iterations for the algorithm to run.
    ALGORITHM == 5 ? 100    : 
    ALGORITHM == 6 ? 100    : 100000000);
constexpr double NAIVE_PROBABILITY = 0.3;                   /// This probability is used in the Naive Heinritz - Hsiao approach of the TSP. This probability means that
                                                            /// there is a 70% chance that the algorithm will choose the nearest point to add to its path, and 30% chance
                                                            /// to choose the second nearest point to add to its path. This variable must never be set above 0.5.

constexpr int BOOST = 10;                                   /// This variable boosts the ammount of pherormone added to the edge chosen by the ant. 
                                                            /// This makes ACS convergence better, regarding time complexity.
constexpr int N_ANTS = 12;                                  /// This is the ammount of ants running. This number also represents the ammount of ***threads*** running 
                                                            /// for the parallel version of the ACS.
constexpr int ANT_MEMORY = (TEST_MODE == 1 ? 5 : 100);      /// This sets the ant memory. This means that each ant gets to cross 100 points, and since each ant starts 
                                                            /// from a different point of the map, there is a pretty high probability that the ants will cover all the 
                                                            /// map by the end of the algorithm. That is if `N_ANTS` multiplied by `ANT_MEMORY` is greater than `N_POINTS`. 
                                                            /// Finally, this variable must always be greater than `N_POINTS`.
constexpr int ROULETTE_SIZE = (TEST_MODE == 1 ? 3 : 4);     /// This the size of the roulette wheel. The roulette wheel is a decision making module that is used in the 
                                                            /// ACS algorithm. This is to solve the computational error that surfaces due to the huge number of possible 
                                                            /// paths the ant can follow. This variable must be changed with respect to the total number of points and to the 
                                                            /// size of the ant memory. The math for this variable is that is has to be less than `N_POINTS` minus `ANT_MEMORY`.
constexpr double RHO = 0.1;                                 /// This is the vaporazation ratio for the ACS.
constexpr int CHUNK = (int)(4 * (N_POINTS / N_ANTS));       /// Sets chunk size for OpenMP loop
