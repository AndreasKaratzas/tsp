
/**
 * Interface.h
 * 
 * In this header file, we define some functions which
 * implement a basic User Interface (UI) for the different
 * approaches to the TSP.
 */

#pragma once

#include "Common.h"

void print_tsp_tour_cost(const std::vector<long double> cost);
void print_cities(const std::array<std::pair<int, int>, N_POINTS> cities);
void print_row(const std::array<double, N_POINTS>& r);
void print_matrix(const std::vector<std::array<double, N_POINTS>> matrix, const std::string matrix_name);
void print_acs_tsp(const std::vector<int> tsp_route);
