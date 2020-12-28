
/**
 * City.h
 * 
 * In this header file, we define a function that is executed only in the 
 * beginning of the program. This function is used to generate a random set
 * of points that will play the role of the cities for the TSP. 
 */

#pragma once

#include "Common.h"

void initialize_cities(std::array<std::pair<int, int>, N_POINTS>& cities);
