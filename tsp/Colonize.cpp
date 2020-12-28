
#include "Colonize.h"

/**
 * Initiates colonization sequence.
 * 
 * @param[in] cities the dataset for ACS
 * @param[in, out] pherormone_matrix the matrix (2d array of sizxe `N_POINTS` x `N_POINTS`) with the pherormone ammount left in each edge
 * 
 */
void colonize(
    const std::array<std::pair<int, int>, N_POINTS>     cities,
    std::vector<std::array<double, N_POINTS>>&          pherormone_matrix)
{
    std::vector<std::array<int, N_POINTS>> non_explored(N_ANTS);    /// Declares a vector that holds all possible points.
                                                                    /// This vector is fragmented into an explored part and an non explored part.
                                                                    /// The explored part is separated by  the non explored part by an index `k`.
                                                                    /// On the left of `k` lie the explored nodes, and on the right the non explored. 
                                                                    /// `k` always points to the node where each ant is currently at.
    std::vector<std::array<std::pair<int, double>, ANT_MEMORY>> explored(N_ANTS);
                                                                    /// Declares a vector that holds the points that the ant has crossed.
                                                                    /// This vector has mainly debugging purposes. However, it is not memory demanding.

    std::random_device ant_rd;                                      /// non-deterministic generator
    std::mt19937 ant_gen(ant_rd());                                 /// to seed mersenne twister
    std::uniform_int_distribution<int> ant_dist(0, N_POINTS - 1);   /// distribute results between 0 and N_POINTS exclusive

    std::random_device wheel_rd;                                    /// non-deterministic generator
    std::mt19937 wheel_gen(wheel_rd());                             /// to seed mersenne twister
    std::uniform_real_distribution<double> wheel_dist(0, 1);        /// distribute results between 0 and 1 inclusive

    for (int i = 0; i < ITERATIONS; i += 1)
    {
        std::cout << "Iteration [" << i << "]" << std::endl;        /// Prints progress info of the ACS since it takes some times to colonize the map
        for (int j = 0; j < N_ANTS; j += 1)
        {
            std::iota(non_explored.at(j).begin(), non_explored.at(j).end(), 0);
                                                                    /// Initializes `non_explored` for the `j`-th ant
            explored.at(j).at(0) = std::make_pair(ant_dist(ant_gen), 0.0);
                                                                    /// Initializes `explored` for the `j`-th ant
            for (int k = 0; k < ANT_MEMORY - 1; k += 1)
            {
                int idx = find(non_explored.at(j), explored.at(j).at(k).first);
                                                                    /// Locates the index of the previously added node
                std::swap(non_explored.at(j).at(k), non_explored.at(j).at(idx));
                                                                    /// Places previously added node on the left of index `k` into `non_explored`
                std::vector<std::pair<int, double>> evaluation;     /// Declares a vector to store all possible edge evaluations
                evaluation.reserve(N_POINTS - k);                   /// Reserves the proper memory size to increase performance
                evaluate_universe(non_explored, j, k, pherormone_matrix, cities, evaluation);
                                                                    /// Evaluates all possible edges 
                int chosen_idx = roulette_wheel(evaluation, wheel_dist(wheel_gen));
                                                                    /// Calls roulette_wheel() to get the chosen edge
                explored.at(j).at(k + 1) = std::make_pair(chosen_idx, BOOST / tsp_hop_cost(cities.at(explored.at(j).at(k).first), cities.at(chosen_idx)).second);
                                                                    /// Updates `explored` vector
                pherormone_matrix.at(explored.at(j).at(k).first).at(explored.at(j).at(k + 1).first) += explored.at(j).at(k + 1).second;
                                                                    /// Updates pherormone matrix
            }
        }
        for (int j = 0; j < N_POINTS; j += 1)                       /// Vaporization loop
        {
            for (int k = 0; k < N_POINTS; k += 1)
            {
                pherormone_matrix.at(j).at(k) = (1 - RHO) * pherormone_matrix.at(j).at(k);
            }                                                       /// Vaporizes pherormone in each edge
        }
    }
}

/**
 * Initiates colonization sequence. This is a fork of the `colonize` function above, parallelized with OpenMP 4.0.
 *
 * @param[in] cities the dataset for ACS
 * @param[in, out] pherormone_matrix the matrix (2d array of sizxe `N_POINTS` x `N_POINTS`) with the pherormone ammount left in each edge
 *
 */
void colonize_parallel(
    const std::array<std::pair<int, int>, N_POINTS>     cities,
    std::vector<std::array<double, N_POINTS>>&          pherormone_matrix)
{
    std::array<int, N_POINTS> non_explored;                         /// In the parallel fork, the `non_explored` array is set private for each ant (each ant represents a thread).
    std::array<std::pair<int, double>, ANT_MEMORY> explored;        /// In the parallel fork, the `explored` array is set private for each ant (each ant represents a thread).

    std::random_device ant_rd;
    std::mt19937 ant_gen(ant_rd());
    std::uniform_int_distribution<int> ant_dist(0, N_POINTS - 1);

    std::random_device wheel_rd;
    std::mt19937 wheel_gen(wheel_rd());
    std::uniform_real_distribution<double> wheel_dist(0, 1);

    for (int i = 0; i < ITERATIONS; i += 1)
    {
        std::cout << "Iteration [" << i << "]" << std::endl;
#pragma omp parallel for num_threads(N_ANTS) private(non_explored, explored) schedule(runtime)
        for (int j = 0; j < N_ANTS; j += 1)
        {
            std::iota(non_explored.begin(), non_explored.end(), 0);
            explored.at(0) = std::make_pair(ant_dist(ant_gen), 0.0);
            for (int k = 0; k < ANT_MEMORY - 1; k += 1)
            {
                int idx = find(non_explored, explored.at(k).first);
                std::swap(non_explored.at(k), non_explored.at(idx));
                std::vector<std::pair<int, double>> evaluation;
                evaluation.reserve(N_POINTS - k);
                evaluate_universe_parallel(non_explored, k, pherormone_matrix, cities, evaluation);
                int chosen_idx = roulette_wheel(evaluation, wheel_dist(wheel_gen));
                explored.at(k + 1) = std::make_pair(chosen_idx, BOOST / tsp_hop_cost(cities.at(explored.at(k).first), cities.at(chosen_idx)).second);
#pragma omp critical
                pherormone_matrix.at(explored.at(k).first).at(explored.at(k + 1).first) += explored.at(k + 1).second;
            }
        }
#pragma omp parallel for collapse(2) schedule(dynamic, CHUNK)
        for (int j = 0; j < N_POINTS; j += 1)
        {
            for (int k = 0; k < N_POINTS; k += 1)
            {
                pherormone_matrix.at(j).at(k) = (1 - RHO) * pherormone_matrix.at(j).at(k);
            }
        }
    }
}

/**
 * Finds TSP route based on pherormone matrix.
 *
 * This implementation is based on elitism from genetic algorithms.
 * This means that for the released TSP route, only the best solutions
 * based on the `pherormone_matrix` will be concatenated to form the TSP route.
 * 
 * @param[in] pherormone_matrix the matrix with the pherormone ammount left in each edge
 * @param[in, out] tsp_route the node indexes with respecto to `cities` variable
 * 
 * @remark https://en.cppreference.com/w/cpp/algorithm/iota
 * @remark https://en.cppreference.com/w/cpp/algorithm/transform
 * @remark https://en.cppreference.com/w/cpp/algorithm/sort
 * @remark https://en.cppreference.com/w/cpp/utility/functional/bind
 * 
 */
void acs_tsp(
    const std::vector<std::array<double, N_POINTS>>     pherormone_matrix,
    std::vector<int>&                                   tsp_route)
{
    tsp_route.emplace_back(0);
    for (int i = 0; i < N_POINTS - 1; i += 1)
    {
        std::vector<double> pherormone_column;                      /// Declares a vector to store the a column from `pherormone_matrix` variable
        std::vector<int> pherormone_idx(N_POINTS);                  /// Declares a vector to be used to associate each value in `pherormone_column` variable with a node
        std::vector<std::pair<int, double>> roulette(N_POINTS);     /// Declares a vector to bind the vectors above
        copy(pherormone_matrix, tsp_route.at(i), pherormone_column);/// Calls copy() from Operation.h and copies column of `pherormone_matrix` variable into `pherormone_column`
        std::iota(pherormone_idx.begin(), pherormone_idx.end(), 0); /// Initializes `pherormone_idx`
        std::transform(pherormone_idx.begin(), pherormone_idx.end(), pherormone_column.begin(), roulette.begin(), std::bind(f, std::placeholders::_1, std::placeholders::_2));
                                                                    /// Binds `pherormone_column` and `pherormone_idx` into `roulette`
        std::sort(roulette.begin(), roulette.end(), sortbysec_dbl); /// Sorts `roulette` vector 
        filter(roulette, tsp_route);                                /// Filters `roulette` based on the route computed by the i'th iteration in order to avoid selecting a node that has already been explored
        tsp_route.emplace_back(roulette.back().first);              /// Updates `tsp_route` vector with the selected node
    }
}
