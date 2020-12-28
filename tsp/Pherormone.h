
/**
 * Pherormone.h
 * 
 * In this header file, we define a function that
 * executes only in the beginning of the ACS algorithm.
 * This function is used to initialize the pherormone
 * matrix that the ACS will use to colonize a map.
 */

#pragma once

#include "Common.h"

void initialize_pherormone_matrix(std::vector<std::array<double, N_POINTS>>& pherormone_matrix);
