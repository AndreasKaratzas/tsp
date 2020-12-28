
/**
 * Utilities.h
 * 
 * In this header file, we define the functions that
 * bind the different approaches that solve the TSP.
 * For this project, 4 different approaches were asked
 * along with three parallelized version of those.
 */

#pragma once

#include "Common.h"
#include "Distance.h"
#include "Colonize.h"
#include "Interface.h"
#include "Pherormone.h"
#include "Validation.h"

void naive_tsp(std::array<std::pair<int, int>, N_POINTS>& cities);
void naive_tsp_parallel(std::array<std::pair<int, int>, N_POINTS>& cities);
void heinritz_hsiao(std::array<std::pair<int, int>, N_POINTS>& cities);
void naive_heinritz_hsiao(std::array<std::pair<int, int>, N_POINTS>& cities);
void naive_heinritz_hsiao_parallel(std::array<std::pair<int, int>, N_POINTS>& cities);
void ant_colony(const std::array<std::pair<int, int>, N_POINTS> cities);
void ant_colony_parallel(const std::array<std::pair<int, int>, N_POINTS> cities);
