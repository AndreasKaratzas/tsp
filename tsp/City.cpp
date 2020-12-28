
#include "City.h"

/**
 * Initializes `cities` variable.
 * 
 * @param[in, out] cities the random dataset generated for the different TSP approaches
 * 
 * @remark [<random> Engines and Distributions](https:///<docs.microsoft.com/en-us/cpp/standard-library/random?view=msvc-160#engdist) 
 */
void initialize_cities(std::array<std::pair<int, int>, N_POINTS>& cities)
{
    std::random_device x_rd;                                    /// non-deterministic generator
    std::mt19937 x_gen(x_rd());                                 /// to seed mersenne twister
    std::uniform_int_distribution<int> x_dist(0, X_MAX);        /// distribute results between 0 and X_MAX inclusive

    std::random_device y_rd;                                    /// non-deterministic generator
    std::mt19937 y_gen(y_rd());                                 /// to seed mersenne twister
    std::uniform_int_distribution<int> y_dist(0, Y_MAX);        /// distribute results between 0 and Y_MAX inclusive

    for (int i = 0; i < N_POINTS; i += 1)                       /// Initializes all `N_POINTS`
    {
        cities.at(i).first  = x_dist(x_gen);                    /// Generates a random X coordinate for point i
        cities.at(i).second = y_dist(y_gen);                    /// Generates a random Y coordinate for point i
    }
}

/**
 * Sets dataset to the fixed array declared in `Common.h` 
 * 
 * @param[in, out] cities the dataset that is set
 */
void set_fixed_dataset(std::array<std::pair<int, int>, N_POINTS>& cities)
{
    std::copy(std::begin(FIXED_DATASET), std::end(FIXED_DATASET), std::begin(cities));
}