
/**
 * Colonize.h
 * 
 * In this header file, we define some functions
 * regarding the ACS algorithm. The functions initiate 
 * the colonization procedure. There is also a function
 * that estimates the total distance covered by the 
 * travelling salesman (`acs_tsp`).
 */

#pragma once

#include "Naive.h"
#include "Common.h"
#include "Distance.h"
#include "Operation.h"

void acs_tsp(const std::vector<std::array<double, N_POINTS>> pherormone_matrix, std::vector<int>& tsp_route);
void colonize(const std::array<std::pair<int, int>, N_POINTS> cities, std::vector<std::array<double, N_POINTS>>& pherormone_matrix);
void colonize_parallel(const std::array<std::pair<int, int>, N_POINTS> cities, std::vector<std::array<double, N_POINTS>>& pherormone_matrix);
