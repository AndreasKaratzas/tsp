
#include "Driver.h"

/**
 * Implements the driver for the different approaches that solve the TSP.
 * 
 * @return 0, if the executable was terminated normally
 */
int main(void)
{
    std::array<std::pair<int, int>, N_POINTS> cities;                                                                   /// Declares a vector to store the dataset 
    if (FIXED_MODE) { set_fixed_dataset(cities); }                                                                      /// If in FIXED_MODE fix - initialize the dataset 
    else { initialize_cities(cities); }                                                                                 /// Else initialize the dataset with random points
    std::string algorithm;                                                                                              /// Declares a string to associate it with the algorithm running
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();                        /// Declares a starting time point which helps in benchmarking
    switch (ALGORITHM)                                                                                                  /// Depending on the algorithm selected by the user call the appropriate routine
    {
        case 0:
            algorithm.assign("[ALGO 0] \"Naive TSP\"");
            naive_tsp(cities); 
            break;
        case 1:
            algorithm.assign("[ALGO 1] \"Naive TSP\" (Parallel Implementation)");
            naive_tsp_parallel(cities); 
            break;
        case 2:
            algorithm.assign("[ALGO 2] \"TSP with nearest neighbor\"");
            heinritz_hsiao(cities); 
            break;
        case 3:
            algorithm.assign("[ALGO 3] \"TSP with naive nearest neighbor\"");
            naive_heinritz_hsiao(cities); 
            break;
        case 4:
            algorithm.assign("[ALGO 4] \"TSP with naive nearest neighbor\" (Parallel Implementation)");
            naive_heinritz_hsiao_parallel(cities); 
            break;
        case 5:
            algorithm.assign("[ALGO 5] \"ACS TSP\"");
            ant_colony(cities);
            break;
        case 6:
            algorithm.assign("[ALGO 6] \"ACS TSP\" (Parallel Implementation)");
            ant_colony_parallel(cities);
            break;
        default:
            std::cout << "[Warning]: Invalid algorithm setting\n\t[\"Unknown algorithm\" fault masked]" << std::endl;   /// Mask unknown algorithm fault
            break;
    }
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();                          /// Declares an ending time point which helps in benchmarking
    std::chrono::duration<double> elapsed_seconds = end - start;                                                        /// Computes execution time
    std::cout << algorithm << " terminated after " << ITERATIONS << " iterations with a total of " << elapsed_seconds.count() << " seconds" << std::endl;
                                                                                                                        /// Outputs results
    return 0;
}
