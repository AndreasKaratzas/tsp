
#include "Utilities.h"

/**
 * Implements Naive TSP.
 * 
 * @param[in, out] cities 
 * 
 * @note the TSP route is actually generated connecting the different
 *      nodes that are found inside the `cities` variable. Therefore,
 *      to update the TSP route, if a better order of those cities is
 *      found, then we swap the order of the cities to fit to the better
 *      cities order.
 * 
 * @remark Naive TSP: 
 *      - Select 2 random points (cities)
 *      - Compute current TSP tour cost
 *      - Permutate those cities
 *      - Recompute the TSP tour cost
 *      - If the later cost is less, then keep the later TSP route
 *      - Else change it back the way it was
 */
void naive_tsp(std::array<std::pair<int, int>, N_POINTS>& cities)
{
    std::random_device rd;                                      /// non-deterministic generator
    std::mt19937 gen(rd());                                     /// to seed mersenne twister
    std::uniform_int_distribution<int> dist(1, N_POINTS - 2);   /// distribute results between 0 and N_POINTS - 2 squared inclusive

    for (int i = 0; i < ITERATIONS; i += 1)
    {
        int point_index_one = dist(gen);                        /// Select the first point for the algorithm
        int point_index_two = dist(gen);                        /// Select the second point for the algorithm
        int is_neighbor = (std::abs(point_index_one - point_index_two) == 1 ? 1 : 0);
                                                                /// Set the neighbor flag with respect to the selected nodes
        if(is_neighbor == 1 && point_index_one > point_index_two) { std::swap(point_index_one, point_index_two); }
                                                                /// Sort points in ascending order if those are neighbors to solve fault in distance computation
        long double diff_before = euclidean_difference(is_neighbor,
            cities.at(point_index_one - 1),
            cities.at(point_index_one),
            cities.at(point_index_one + 1),
            cities.at(point_index_two - 1),
            cities.at(point_index_two),
            cities.at(point_index_two + 1));                    /// Compute the TSP tour cost before permutation
        long double diff_after = euclidean_difference(is_neighbor,
            cities.at(point_index_one - 1),
            cities.at(point_index_two),
            cities.at(point_index_one + 1),
            cities.at(point_index_two - 1),
            cities.at(point_index_one),
            cities.at(point_index_two + 1));                    /// Compute the TSP tour cost after the permutation
        if (diff_before > diff_after)                           /// Compare the two computed costs
        {
            std::swap(cities.at(point_index_one), cities.at(point_index_two));
                                                                /// Change the order of the cities if random permutation gave better results
            if (TEST_MODE)
            {
                std::cout << "ITERATION [ " << i << " ]\t";     /// If in debug mode, print out some information on the algorithm's progress
                print_tsp_tour_cost(tsp_tour_cost(cities)); 
                export_graph_newtork_array(cities, "graph" + std::to_string(i));
                                                                /// Export the new order of nodes to a CSV file
            }
        }
    }
}

/**
 * Implements Naive TSP. This is a fork of the `naive_tsp` function above, parallelized with OpenMP 4.0.
 *
 * @param[in, out] cities
 */
void naive_tsp_parallel(std::array<std::pair<int, int>, N_POINTS>& cities)
{
    std::random_device rd;                                      /// non-deterministic generator
    std::mt19937 gen(rd());                                     /// to seed mersenne twister
    std::uniform_int_distribution<int> dist(1, N_POINTS - 2);   /// distribute results between 0 and N_POINTS - 2 inclusive

    std::random_device perm_rd;                                 /// non-deterministic generator
    std::mt19937 perm_gen(perm_rd());                           /// to seed mersenne twister
    std::uniform_real_distribution<float> perm_dist(0, 1);      /// distribute results between 0 and 1 inclusive

    for (int i = 0; i < ITERATIONS; i += 1)                     /// Precompute around {`N_POINTS` divided by 2} permutations 
    {
        std::vector<int> permutations;
        permutations.reserve((int)(N_POINTS / 2));
        float const_prob = 0.0;
        for (int j = 1; j < N_POINTS - 2; j += 1)
        {
            if (perm_dist(perm_gen) - const_prob > NAIVE_PROBABILITY)
            {
                permutations.push_back(j);                      /// If a node is chosen to be added in the permutation vector 
                const_prob = 1.0;                               /// then make sure not to chose a neighbor, since the permutations will be executed
            }                                                   /// in parallel and there is a chance of a false distance calculation
            else
            {
                const_prob = 0.0;
            }
        }

        std::shuffle(permutations.begin(), permutations.end(), std::mt19937{ std::random_device{}() });
                                                                /// Shuffle the permutation vector precomputed above to generate random pairs for permutation
#pragma omp parallel for num_threads(N_THREADS) schedule(runtime)
        for (int k = 0; k < permutations.size() - 1; k += 2)
        {
            int point_index_one = permutations.at(k);
            int point_index_two = permutations.at(k + 1);
            int is_neighbor = (std::abs(point_index_one - point_index_two) == 1 ? 1 : 0);
            long double diff_before = euclidean_difference(is_neighbor,
                cities.at(point_index_one - 1),
                cities.at(point_index_one),
                cities.at(point_index_one + 1),
                cities.at(point_index_two - 1),
                cities.at(point_index_two),
                cities.at(point_index_two + 1));
            long double diff_after = euclidean_difference(is_neighbor,
                cities.at(point_index_one - 1),
                cities.at(point_index_two),
                cities.at(point_index_one + 1),
                cities.at(point_index_two - 1),
                cities.at(point_index_one),
                cities.at(point_index_two + 1));
            if (diff_before > diff_after)
            {
                std::swap(cities.at(point_index_two), cities.at(point_index_one));
                if (TEST_MODE)
                {
#pragma omp critical
                    {
                        print_tsp_tour_cost(tsp_tour_cost(cities));
                        export_graph_newtork_array(cities, "graph" + std::to_string(i));
                    }
                }
            }
        }
    }
}

/**
 * Implements TSP with nearest neighbor, or
 * as the project states the Heinritz - Hsiao algorithm.
 * 
 * @param[in, out] cities the dataset which is to be optimized
 * 
 * @remark Heinritz - Hsiao:
 *      - Place the travelling salesman in a city
 *      - Repeat:
 *      -   Find the closest city to the city the salesman is at
 *      -   Go to that city
 *      - Until all cities have been explored
 */
void heinritz_hsiao(std::array<std::pair<int, int>, N_POINTS>& cities)
{
    for (int i = 0; i < N_POINTS - 1; i += 1)
    {
        long double min_val = std::numeric_limits<double>::infinity();
        int min_idx = -1;
        for (int j = i + 1; j < N_POINTS; j += 1)           /// Iterate through all possible cities and find the one with the minimum Euclidean distance
        {
            long double cost = tsp_hop_cost(cities.at(i), cities.at(j)).second;
            if (cost < min_val)                             /// If a (local) minimum is found, update indicators
            {
                min_idx = j;
                min_val = cost;
            }
        }
        std::swap(cities.at(i + 1), cities.at(min_idx));    /// Swap the city order with respect to the selected city
        if (TEST_MODE)                                      /// If in debug mode, print out some information on the algorithm's progress
        {
            std::cout << "[ITERATION " << i << "]";
            print_tsp_tour_cost(tsp_tour_cost(cities));
            export_graph_newtork_array(cities, "graph" + std::to_string(i));
        }
    }
}

/**
 * Implements TSP with naive nearest neighbor.
 *
 * @param[in, out] cities the dataset which is to be optimized
 *
 * @remark Naive Heinritz - Hsiao:
 *      - Place the travelling salesman in a city
 *      - Repeat:
 *      -   Find the 2 closest cities to the city the salesman is at
 *      -   Randomly one of those cities
 *      -   Go to that city
 *      - Until all cities have been explored
 */
void naive_heinritz_hsiao(std::array<std::pair<int, int>, N_POINTS>& cities)
{
    std::random_device naive_rd;                                /// non-deterministic generator
    std::mt19937 naive_gen(naive_rd());                         /// to seed mersenne twister
    std::uniform_real_distribution<double> naive_dist(0, 1);    /// distribute results between 0 and 1 inclusive
    for (int i = 0; i < N_POINTS - 2; i += 1)
    {
        std::array<int, 2> neighbors_idx;                       /// Declare an array to store the indexes corresponding to the two closest cities
        long double min_val = std::numeric_limits<double>::infinity();
        for (int j = i + 1; j < N_POINTS; j += 1)
        {
            long double cost = tsp_hop_cost(cities.at(i), cities.at(j)).second;
            if (cost < min_val)                                 /// If a (local) minimum is found, then update `neighbors_idx` array
            {
                min_val = cost;
                std::swap(neighbors_idx.at(0), neighbors_idx.at(1));
                neighbors_idx.at(0) = j;
            }
        }
        std::swap(cities.at(i + 1), cities.at(neighbors_idx.at((NAIVE_PROBABILITY > naive_dist(naive_gen) ? 1 : 0))));
                                                                /// Swap the city order with respect to the two closest cities given a `NAIVE_PROBABILITY`
        if (TEST_MODE)                                          /// If in debug mode, print out some information on the algorithm's progress
        {
            std::cout << "[ITERATION " << i << "]";
            print_tsp_tour_cost(tsp_tour_cost(cities));
            export_graph_newtork_array(cities, "graph" + std::to_string(i));
        }
    }
}

/**
 * Implements TSP with naive nearest neighbor. This is a fork of the `naive_heinritz_hsiao` function above, parallelized with OpenMP 4.0.
 *
 * @param[in, out] cities the dataset which is to be optimized
 */
void naive_heinritz_hsiao_parallel(std::array<std::pair<int, int>, N_POINTS>& cities)
{
    std::random_device naive_rd;                                /// non-deterministic generator
    std::mt19937 naive_gen(naive_rd());                         /// to seed mersenne twister
    std::uniform_real_distribution<double> naive_dist(0, 1);    /// distribute results between 0 and 1 inclusive
    for (int i = 0; i < N_POINTS - 2; i += 1)
    {
        std::array<std::array<int, 2>, N_THREADS> neighbors_idx;
        std::array<std::array<long double, 2>, N_THREADS> neighbors_val;
        for (int j = 0; j < N_THREADS; j += 1)
        {
            neighbors_idx.at(j).fill(i + 1);
            neighbors_val.at(j).fill(std::numeric_limits<long double>::infinity());
        }
#pragma omp parallel for num_threads(N_THREADS) schedule(runtime)
        for (int j = i + 1; j < N_POINTS; j += 1)               /// Each threads finds its own pair of closest cities
        {
            long double cost = tsp_hop_cost(cities.at(i), cities.at(j)).second;
            if (cost < neighbors_val.at(omp_get_thread_num()).at(1))
            {
                if (cost < neighbors_val.at(omp_get_thread_num()).at(0))
                {
                    neighbors_idx.at(omp_get_thread_num()).at(0) = j;
                    std::swap(neighbors_idx.at(omp_get_thread_num()).at(0), neighbors_idx.at(omp_get_thread_num()).at(1));
                    neighbors_val.at(omp_get_thread_num()).at(0) = cost;
                    std::swap(neighbors_val.at(omp_get_thread_num()).at(0), neighbors_val.at(omp_get_thread_num()).at(1));
                }
                else
                {
                    neighbors_idx.at(omp_get_thread_num()).at(1) = j;
                    neighbors_val.at(omp_get_thread_num()).at(1) = cost;
                }
            }
        }
        std::array<int, 2> reduced_cost_idx;
        std::array<long double, 2> reduced_cost_val;
        reduced_cost_val.fill(std::numeric_limits<long double>::infinity());
        for (int j = 0; j < N_THREADS; j += 1)                  /// When all threads are done comparing distances, this final comparison is performed.
        {                                                       /// The difference is that now, only N_THREADS x 2 values have to be compared, not N_POINTS x 2.
            for (int k = 0; k < neighbors_val.at(j).size(); k += 1)
            {
                if (neighbors_val.at(j).at(k) < reduced_cost_val.at(1) && neighbors_val.at(j).at(k) > 0.0)
                {                                               /// Update `reduced_cost_idx`, which is the container with the final 2 closest cities
                    if (neighbors_val.at(j).at(k) < reduced_cost_val.at(0))
                    {                                           /// A better minimum was found
                        std::swap(reduced_cost_idx.at(0), reduced_cost_idx.at(1));
                        reduced_cost_idx.at(0) = neighbors_idx.at(j).at(k);
                        std::swap(reduced_cost_val.at(0), reduced_cost_val.at(1));
                        reduced_cost_val.at(0) = neighbors_val.at(j).at(k);
                    }
                    else
                    {                                           /// A second better minimum was found
                        reduced_cost_idx.at(1) = neighbors_idx.at(j).at(k);
                        reduced_cost_val.at(1) = neighbors_val.at(j).at(k);
                    }
                }
            }
        }
        std::swap(cities.at(i + 1), cities.at(reduced_cost_idx.at((NAIVE_PROBABILITY > naive_dist(naive_gen) ? 1 : 0))));
                                                                /// Update the city order with respect to the `reduced_cost_idx`
        if (TEST_MODE)                                          /// If in debug mode, print out some information on the algorithm's progress
        {
            std::cout << "[ITERATION " << i << "][SECOND HIGHEST COST " << reduced_cost_val.at((NAIVE_PROBABILITY > naive_dist(naive_gen) ? 1 : 0)) << "]\t";
            print_tsp_tour_cost(tsp_tour_cost(cities));
            export_graph_newtork_array(cities, "graph" + std::to_string(i));
        }
    }
}

/**
 * Implements ACS.
 * 
 * param[in] cities the dataset of the random cities to be explored
 * 
 * @note the ACS requires a huge ammount of memory. Only the pherormone matrix
 *          requires 100 million double values to be stored, which is around 850 MB 
 *          of memory (according to the Visual Studio Memory Profiler). Then, there
 *          is the `non_explored` vector which is necessary since it keeps a track of 
 *          each ant's explored nodes.
 * 
 * @remark Ant colony:
 *          - Place N_ANTS in random cities
 *          - For each ant repeat:
 *          -   Evaluate all the possible edges
 *          -   Fetch each edge's pherormone
 *          -   Select an edge using Roulette Wheel
 *          -   Leave some pherormone on that edge
 *          - Until ANT_MEMORY is exceeded
 * 
 * @remark https://staff.washington.edu/paymana/swarm/stutzle99-eaecs.pdf
 * 
 * @remark https://youtu.be/783ZtAF4j5g
 */
void ant_colony(const std::array<std::pair<int, int>, N_POINTS> cities)
{
    std::vector<std::array<double, N_POINTS>> pherormone_matrix(N_POINTS);
                                                                /// Declare the pherormone matrix of dimentions N_POINTS x N_POINTS
    initialize_pherormone_matrix(pherormone_matrix);            /// Initialize the pherormone matrix
    std::vector<int> tsp_route;                                 /// Initialize a variable to store the TSP route found by the ants
    tsp_route.reserve(N_POINTS);                                /// Reserve `N_POINTS` of memory slots to increase performance
    colonize(cities, pherormone_matrix);                        /// Colonize the map
    if (TEST_MODE)                                              /// If in debug mode, print out some information on the algorithm's progress
    {
        print_matrix(pherormone_matrix, "Pherormone Matrix");
        acs_tsp(pherormone_matrix, tsp_route);
        double acs_cost = acs_tsp_cost(tsp_route, cities);
        print_acs_tsp(tsp_route);
        std::cout << "\tCost estimated by \"ACS\": " << acs_cost << std::endl;
        export_acs_tsp_route(cities, "acs_tsp", tsp_route);
    }
}

/**
 * Implements ACS. This is a fork of the `ant_colony` function above, parallelized with OpenMP 4.0.
 *
 * param[in] cities the dataset of the random cities to be explored
 *
 * @note the parallel version of the ACS requires an even greater ammount of memory
 *          to be reserved. For 10,000 cities, the ammount of memory reserved was
 *          12 GB. That is why the number of cities, which is declared by `N_POINTS`
 *          is better to be less than 2,000 when running ACS.
 */
void ant_colony_parallel(const std::array<std::pair<int, int>, N_POINTS> cities)
{
    std::vector<std::array<double, N_POINTS>> pherormone_matrix(N_POINTS);
    initialize_pherormone_matrix(pherormone_matrix);
    std::vector<int> tsp_route;
    tsp_route.reserve(N_POINTS);
    colonize_parallel(cities, pherormone_matrix);               /// Call the parallel version of the colonize() function
    if (TEST_MODE)
    {
        print_matrix(pherormone_matrix, "Pherormone Matrix");
        acs_tsp(pherormone_matrix, tsp_route);
        double acs_cost = acs_tsp_cost(tsp_route, cities);
        print_acs_tsp(tsp_route);
        std::cout << "\tCost estimated by \"ACS\": " << acs_cost << std::endl;
        export_acs_tsp_route(cities, "acs_tsp", tsp_route);
    }
}
