
/**
 * City.h
 * 
 * In this header file, we define some functions that are executed
 * only in the beginning of the program. These functions are used
 * either to generate a random set or to set the dataset to a
 * fixed state of points that will play the role of the cities
 * for the TSP. 
 */

#pragma once

#include "Common.h"

void initialize_cities(std::array<std::pair<int, int>, N_POINTS>& cities);
void set_fixed_dataset(std::array<std::pair<int, int>, N_POINTS>& cities);
