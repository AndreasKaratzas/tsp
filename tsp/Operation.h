
/**
 * Operation.h
 * 
 * In this header file, we define some functions that
 * implement generic operations like complex comparison  
 * in a container or vector normalization.
 */

#pragma once

#include "Common.h"

/**
 * Finds the lower bound from inside pair by the first pair element
 * 
 * @param[in] value a std::pair container. Its first element will be compared with the second given parameter
 * @param[in] key this is the second parameter used for comparison
 * 
 * @return boolean value that indicates equality or not
 * 
 * @note This is the implementation for integer comparison
 * 
 * @remark https://en.cppreference.com/w/cpp/algorithm/lower_bound
 */
struct compare_int
{
    bool operator()(const std::pair<int, int>& value, const int& key) { return (value.first == key); }
    bool operator()(const int& key, const std::pair<int, int>& value) { return (key == value.first); }
};

/**
 * Finds the lower bound from inside pair by the first pair element
 *
 * @param[in] value a std::pair container. Its first element will be compared with the second given parameter
 * @param[in] key this is the second parameter used for comparison
 *
 * @return boolean value that indicates equality or not
 *
 * @note This is the implementation for double precision number comparison
 *
 * @remark https://en.cppreference.com/w/cpp/algorithm/lower_bound
 */
struct compare_dbl
{
    bool operator()(const std::pair<int, double>& value, const double& key) { return (value.second < key); }
    bool operator()(const double& key, const std::pair<int, double>& value) { return (key < value.second); }
};

int find(const std::array<int, N_POINTS> non_explored, const int element);
bool sortbysec_dbl(const std::pair<int, double>& a, const std::pair<int, double>& b);
bool sortbysec_int(const std::pair<int, int>& a, const std::pair<int, int>& b);
int search(const std::vector<std::pair<int, double>> container, double value);
std::pair<int, double> normalized_value(std::pair<int, double> p, double min, double max);
void normalize(std::vector<std::pair<int, double>>& evaluation);
void copy(const std::vector<std::array<double, N_POINTS>> pherormone_matrix, const int col_idx, std::vector<double>& pherormone_column);
void filter(std::vector<std::pair<int, double>>& roulette, const std::vector<int> tsp_route);
std::pair<int, double> f(int i, double d);
