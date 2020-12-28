
#include "Operation.h"

/**
 * Finds element inside an array.
 * 
 * @param[in] non_explored the array to be parsed
 * @param[in] element the element to be found
 * 
 * @return the index from the array associated with the given element
 * 
 * @note there is a redundancy to trace the "Element Not Found" fault.
 */
int find(const std::array<int, N_POINTS> non_explored, const int element)
{
    std::array<int, N_POINTS>::const_iterator it = std::find(non_explored.begin(), non_explored.end(), element);
    if (it == non_explored.end())
    {
        std::cout << "[WARNING]: Element not found" << std::endl;
    }
    return it - non_explored.begin();
}

/**
 * Sorts a vector of pairs in ascending order by second element of pairs.
 * 
 * @param[in] a the first pair
 * @param[in] b the second pair
 * 
 * @return boolean that indicates if the first element was greater than the second or not
 * 
 * @note Only second elements of the given pairs were compared
 *
 * @remark https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/
 */
bool sortbysec_dbl(const std::pair<int, double>& a, const std::pair<int, double>& b)
{
    return (a.second < b.second);
}

/**
 * Sorts a vector of pairs in ascending order by second element of pairs. This is a fork of the function sortbysec_dbl() implemented for integer comparison.
 *
 * @param[in] a the first pair
 * @param[in] b the second pair
 *
 * @return boolean that indicates if the first element was greater than the second or not
 *
 * @note Only second elements of the given pairs were compared
 *
 * @remark https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/
 */
bool sortbysec_int(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return (a.second < b.second);
}

/**
 * Searches a vector of pairs for a value.
 * 
 * @param[in] container the container to be searched
 * @param[in] value the value that we are trying to locate inside the container
 * 
 * @return the index pointing to the element corresponding to the given value
 * 
 * @note this function is called to find the proper element chosen by the roulette wheel selection algorithm
 * 
 * @remark Naive.h
 */
int search(const std::vector<std::pair<int, double>> container, double value)
{
    std::vector<std::pair<int, double>>::const_iterator it = std::lower_bound(container.begin(), container.end(), value, compare_dbl());
    return container.at((it - container.begin())).first;
}

/**
 * Normalizes double values.
 * 
 * @param[in] p the pair that we want to normalize
 * @param[in] min the minimum value found in the container
 * @param[in] max the maximum value found in the container
 * 
 * @return the normalized pair 
 * 
 * @note only the second element of the container is to be normalized.
 *      This function is only called by function normalize() below.
 */
std::pair<int, double> normalized_value(std::pair<int, double> p, double min, double max) { return std::make_pair(p.first, (p.second - min) / (max - min)); }

/**
 * Normalizes a container.
 * 
 * @param[in, out] evaluation the container to be normalized
 * 
 * @remark https://en.cppreference.com/w/cpp/algorithm/transform
 */
void normalize(std::vector<std::pair<int, double>>& evaluation)
{
    double min = evaluation.at(0).second;
    double max = evaluation.at(evaluation.size() - 1).second;
    std::transform(evaluation.begin(), evaluation.end(), evaluation.begin(), std::bind(normalized_value, std::placeholders::_1, min, max));
}

/**
 * Copies column of a matrix.
 * 
 * @param[in] pherormone_matrix the matrix from which data will be copied
 * @param[in] col_idx the index corresponding column from `pherormone_matrix` to be copied
 * @param[in, out] pherormone_column the vector in which data will be copied
 */
void copy(const std::vector<std::array<double, N_POINTS>> pherormone_matrix, const int col_idx, std::vector<double>& pherormone_column)
{
    pherormone_column.reserve(N_POINTS);
    for (int j = 0; j < N_POINTS; j += 1)
    {
        pherormone_column.emplace_back(pherormone_matrix.at(j).at(col_idx));
    }
}

/**
 * Custom vector filter. 
 * 
 * @param[in, out] roulette the vector to be filtered
 * @param[in] tsp_route the vector based on which elements will be deleted
 * 
 * @note this is called to filter the roulette vector based on current tsp route. This prevents node repetition throughout the route
 */
void filter(std::vector<std::pair<int, double>>& roulette, const std::vector<int> tsp_route)
{
    for (int i = 0; i < tsp_route.size(); i += 1)
    {
        for (int j = 0; j < roulette.size(); j += 1)
        {
            if (tsp_route.at(i) == roulette.at(j).first)
            {
                roulette.erase(roulette.begin() + j);       /// Deletes any element found in tsp_route.
            }                                               /// That way the ants are encouraged to select unexplored nodes.
        }
    }
}
/**
 * This function is called to bind an integer and a double into an std::pair
 * 
 * @param[in] i the integer variable
 * @param[in] d the double variable
 * 
 * @return the pair containing the given variables
 */
std::pair<int, double> f(int i, double d) { return std::make_pair(i, d); }
