
/**
 * Naive.h
 * 
 * In this header file, we define a function that
 * implements the roulette wheel selection algorithm,
 * also known as the fitness proportionate selection.
 * It is an algorithm that is used to select an item
 * that corresponds to its probability or odds.
 */

#pragma once

#include "Common.h"
#include "Operation.h"

int roulette_wheel(std::vector<std::pair<int, double>>& evaluation, double roulette_random);
