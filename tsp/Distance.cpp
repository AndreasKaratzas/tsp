
#include "Distance.h"

/**
 * Computes the Euclidean distance of 2 given points.
 * 
 * @param[in] point_one this is the first point
 * @param[in] point_two this is the second point
 * 
 * @return std::pair<int, double> where the integer is an possible overflow warning flag, and the double value is the Euclidean distance
 */
std::pair<int, long double> tsp_hop_cost(const std::pair<int, int> point_one, const std::pair<int, int> point_two)
{
    std::pair<int, long double> diff;                       /// Declare the return variable
    diff.second = sqrt(((point_one.first - point_two.first) * (point_one.first - point_two.first)) +
        ((point_one.second - point_two.second) * (point_one.second - point_two.second)));
                                                            /// Compute Euclidean distance
    if (diff.second > std::numeric_limits<double>::max())   /// Check for possible overflow
    {
        diff.second = std::numeric_limits<double>::max();   /// Mask overflow
        diff.first = 1;                                     /// Set overflow warning flag
    }
    else
    {
        diff.first = 0;                                     /// Deactivate overflow warning flag
    }

    return diff;
}

/**
 * Accumulates all costs and computes total TSP tour cost.
 * 
 * @param[in] cities the preprocessed dataset
 * 
 * @return a vector of distances
 * 
 * @note if the module detects possible overflow, then it pushes back to 
 *     the vector a new double element and updates that element. The sum
 *     of all those elements is the total distance which due to computer
 *     overflow warning are separated using that vector.
 */
std::vector<long double> tsp_tour_cost(const std::array<std::pair<int, int>, N_POINTS> cities)
{
    std::vector<long double> cost;                          /// Declares the costs vector
    cost.reserve(10);                                       /// Reserves a proper ammount of memory 
    int overflow = 1;                                       /// Sets overflow flag
    for (int i = 0; i < cities.size() - 1; i += 1)
    {
        std::pair<int, long double> diff = tsp_hop_cost(cities.at(i), cities.at(i + 1));
                                                            /// Computes the Euclidean distance between 2 points 
        if (overflow)                                       /// Masks possible overflow error
        {
            cost.push_back(diff.second);                    /// Creates amd updates a new element
        }
        else
        {
            cost.at(cost.size() - 1) += diff.second;        /// Updates cost vector
        }
        overflow = diff.first;                              /// Updates overflow flag
    }
    return cost;
}

/**
 * Computes the Euclidean distance between:
 *      - Point A and its predecessor
 *      - Point A and its successor
 *      - Point B and its predecessor
 *      - Point B and its successor
 * 
 * @param[in] is_neighbor this is a flag indicating that Point A is either a predecessor or a successor of Point B
 * @param[in] pre_point_one this is the predecessor of Point A
 * @param[in] point_one this is Point A
 * @param[in] suc_point_one this is the successor of Point A
 * @param[in] pre_point_two this is the predecessor of Point B
 * @param[in] point_two this is Point B
 * @param[in] suc_point_two this is the successor of Point B
 * 
 * @return the sum of the distances described above.
 * 
 * @note it also masks possible integer overflow fault.
 */
long double euclidean_difference(int is_neighbor,
    const std::pair<int, int> pre_point_one,
    const std::pair<int, int> point_one,
    const std::pair<int, int> suc_point_one,
    const std::pair<int, int> pre_point_two,
    const std::pair<int, int> point_two,
    const std::pair<int, int> suc_point_two)
{
    long int pred_diff_point_one = ((pre_point_one.first - point_one.first) * (pre_point_one.first - point_one.first)) +
        ((pre_point_one.second - point_one.second) * (pre_point_one.second - point_one.second));    /// Computes Euclidean distance between Point A and its predecessor
    long int succ_diff_point_one = ((suc_point_one.first - point_one.first) * (suc_point_one.first - point_one.first)) +
        ((suc_point_one.second - point_one.second) * (suc_point_one.second - point_one.second));    /// Computes Euclidean distance between Point A and its successor
    long int pred_diff_point_two = ((pre_point_two.first - point_two.first) * (pre_point_two.first - point_two.first)) +
        ((pre_point_two.second - point_two.second) * (pre_point_two.second - point_two.second));    /// Computes Euclidean distance between Point B and its predecessor
    long int succ_diff_point_two = ((suc_point_two.first - point_two.first) * (suc_point_two.first - point_two.first)) +
        ((suc_point_two.second - point_two.second) * (suc_point_two.second - point_two.second));    /// Computes Euclidean distance between Point B and its successor
    if (pred_diff_point_one > std::numeric_limits<int>::max())
    {
        pred_diff_point_one = std::numeric_limits<int>::max();                                      /// Masks possible integer overflow in `pred_diff_point_one`
    }
    if (succ_diff_point_one > std::numeric_limits<int>::max())                                      /// Masks possible integer overflow in `succ_diff_point_one`
    {
        succ_diff_point_one = std::numeric_limits<int>::max();
    }
    if (pred_diff_point_two > std::numeric_limits<int>::max())                                      /// Masks possible integer overflow in `pred_diff_point_two`
    {
        pred_diff_point_two = std::numeric_limits<int>::max();
    }
    if (succ_diff_point_two > std::numeric_limits<int>::max())                                      /// Masks possible integer overflow in `succ_diff_point_two`
    {
        succ_diff_point_two = std::numeric_limits<int>::max();
    }

    if (is_neighbor)
    {
        return std::sqrt(pred_diff_point_one) + std::sqrt(succ_diff_point_two);                     /// If the given points are neighbors, it corrects the sum of distance
    }
    else
    {
        return std::sqrt(pred_diff_point_one) + std::sqrt(succ_diff_point_one) + std::sqrt(pred_diff_point_two) + std::sqrt(succ_diff_point_two);
    }
}

/*
 * Evaluates all possible edge costs in ACS.
 * 
 * @param[in] non_explored the vector of the ant path sorted in non explored points and explored ones
 * @param[in] ant_idx the current ant number (index) calling this function to evaluate its path
 * @param[in] last_explored_idx the index to the last explored element in `non_explored` vector
 * @param[in] pherormone_matrix the matrix in which ant pherormone is stored
 * @param[in] cities the dataset generated in the beginning containing the <x, y> coordinates of the points (cities)
 * @param[in, out] evaluation this is the vector where we store each edge cost
 */
void evaluate_universe(
    const std::vector<std::array<int, N_POINTS>>            non_explored,
    const int                                               ant_idx,
    const int                                               last_explored_idx,
    const std::vector<std::array<double, N_POINTS>>         pherormone_matrix,
    const std::array<std::pair<int, int>, N_POINTS>         cities,
    std::vector<std::pair<int, double>>&                    evaluation)
{
    for (int l = last_explored_idx + 1; l < N_POINTS; l += 1)
    {
        double cost = tsp_hop_cost(cities.at(non_explored.at(ant_idx).at(last_explored_idx)), cities.at(non_explored.at(ant_idx).at(l))).second;
                                                            /// Computes the cost between the last explored node and every other possible node
        double pherormone = pherormone_matrix.at(non_explored.at(ant_idx).at(last_explored_idx)).at(non_explored.at(ant_idx).at(l));
                                                            /// Fetches the pherormone assigned to that edge
        evaluation.emplace_back(std::make_pair(non_explored.at(ant_idx).at(l), pherormone * (1 / cost)));
                                                            /// Evaluates that edge based on the cost and its past pherormone
    }
}

/*
 * Evaluates all possible edge costs in ACS. This is a fork of the `evaluate_universe` function above, fine tuned for the parallelized version of ACS.
 *
 * @param[in] non_explored the array of the ant path sorted in non explored points and explored ones
 * @param[in] last_explored_idx the index to the last explored element in `non_explored` vector
 * @param[in] pherormone_matrix the matrix in which ant pherormone is stored
 * @param[in] cities the dataset generated in the beginning containing the <x, y> coordinates of the points (cities)
 * @param[in, out] evaluation this is the vector where we store each edge cost
 */
void evaluate_universe_parallel(
    const std::array<int, N_POINTS>                         non_explored,
    const int                                               last_explored_idx,
    const std::vector<std::array<double, N_POINTS>>         pherormone_matrix,
    const std::array<std::pair<int, int>, N_POINTS>         cities,
    std::vector<std::pair<int, double>>&                    evaluation)
{
    for (int l = last_explored_idx + 1; l < N_POINTS; l += 1)
    {
        double cost = tsp_hop_cost(cities.at(non_explored.at(last_explored_idx)), cities.at(non_explored.at(l))).second;
        double pherormone = pherormone_matrix.at(non_explored.at(last_explored_idx)).at(non_explored.at(l));
        evaluation.emplace_back(std::make_pair(non_explored.at(l), pherormone * (1 / cost)));
    }
}


/**
 * Computes ACS TSP tour cost.
 * 
 * @param[in] tsp_route the tsp route estimated after colonization
 * @param[in] cities the random generated dataset of points (cities)
 * 
 * @return the cost of the estimated TSP route by ACS
 */
double acs_tsp_cost(const std::vector<int> tsp_route, const std::array<std::pair<int, int>, N_POINTS> cities)
{
    double cost = 0.0;
    for (int i = 0; i < tsp_route.size() - 1; i += 1)
    {
        cost += tsp_hop_cost(cities.at(tsp_route.at(i)), cities.at(tsp_route.at(i + 1))).second;
    }
    cost += tsp_hop_cost(cities.at(tsp_route.at(tsp_route.size() - 1)), cities.at(tsp_route.at(0))).second;

    return cost;
}
