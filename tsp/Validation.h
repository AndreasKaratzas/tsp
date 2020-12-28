
/**
 * Validation.h
 * 
 * In this header file, we define some functions
 * used to validate the data computed by the different
 * algorithms using an external program.
 * 
 * @note The external program can be found at https://github.com/andreasceid/csv2networkx
 */

#pragma once

#include "Common.h"

void export_graph_newtork_array(const std::array<std::pair<int, int>, N_POINTS> cities, std::string filename);
void export_acs_tsp_route(const std::array<std::pair<int, int>, N_POINTS> cities, std::string filename, const std::vector<int> tsp_route);
