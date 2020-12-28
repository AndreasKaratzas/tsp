
/**
 * Distance.h 
 * 
 * In this header file, we define the 
 * cost functions used throughout the project.
 * Those functions use Euclidean distance to 
 * estimate the cost of a process.
 */

#pragma once

#include "Common.h"

std::pair<int, long double> tsp_hop_cost(const std::pair<int, int> point_one, const std::pair<int, int> point_two);
std::vector<long double> tsp_tour_cost(const std::array<std::pair<int, int>, N_POINTS> cities);
long double euclidean_difference(int is_neighbor, const std::pair<int, int> pre_point_one, const std::pair<int, int> point_one, const std::pair<int, int> suc_point_one, const std::pair<int, int> pre_point_two, const std::pair<int, int> point_two, const std::pair<int, int> suc_point_two);
void evaluate_universe(const std::vector<std::array<int, N_POINTS>> non_explored, const int ant_idx, const int last_explored_idx, const std::vector<std::array<double, N_POINTS>> pherormone_matrix, const std::array<std::pair<int, int>, N_POINTS> cities, std::vector<std::pair<int, double>>& evaluation);
void evaluate_universe_parallel(const std::array<int, N_POINTS> non_explored, const int last_explored_idx, const std::vector<std::array<double, N_POINTS>> pherormone_matrix, const std::array<std::pair<int, int>, N_POINTS> cities, std::vector<std::pair<int, double>>& evaluation);
double acs_tsp_cost(const std::vector<int> tsp_route, const std::array<std::pair<int, int>, N_POINTS> cities);
