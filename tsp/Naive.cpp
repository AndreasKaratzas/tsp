
#include "Naive.h"

/**
 * Selects an edge for the ant to follow 
 * based on all precomputed evaluations.
 * 
 * @param[in, out] evaluation the precomputed edge evaluations
 * @param[in] roulette_random the precomputed ramdom selection probability
 * 
 * @return the index of the next node for the ant to go
 * 
 * @note this function calls modules from Operation.h
 */
int roulette_wheel(std::vector<std::pair<int, double>>& evaluation, double roulette_random)
{
    std::sort(evaluation.begin(), evaluation.end(), sortbysec_dbl);             /// Sorts all precomputed evaluations
    evaluation.erase(evaluation.begin(), evaluation.end() - ROULETTE_SIZE);     /// Reduces the ammount of the evaluations 
                                                                                /// deleting the less likely to be chosen.
                                                                                /// This masks computationsal error when the
                                                                                /// dataset is too large. It also makes the 
                                                                                /// algorithm's convergence faster.
    double accumulator = 0.0;                                                   /// A variable used to accumulate the different edge evaluations for the roulette wheel
    for (int m = 0; m < evaluation.size(); m += 1)                              /// Reformat all evaluations to feed the roulette wheel selection algorithm
    {
        double temp = evaluation.at(m).second;
        evaluation.at(m).second += accumulator;                                 /// Accumulate previous variable value
        accumulator += temp;                                                    /// Update accumulator
    }
    normalize(evaluation);                                                      /// Normalize the vector
    return search(evaluation, roulette_random);                                 /// Find the selected next node based on the precomputed probability
}
