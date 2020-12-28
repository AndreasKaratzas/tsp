
#include "Interface.h"

/**
 * Prints the cost of a tsp tour.
 * 
 * @param[in] cost the precomputed cost variable
 */
void print_tsp_tour_cost(const std::vector<long double> cost)
{
    std::cout.precision(std::numeric_limits<long double>::max_digits10);            /// Sets I/O stream representation precision in any floating point variable
    for (int i = 0; i < cost.size(); i += 1)
    {
        if (i == 0)
        {
            std::cout << "[ ";
        }
        std::cout << std::setw(12) << cost.at(i) << " ";
        if ((i % 4 == 0) && (cost.size() > i) && (i > 0))                           /// Breaks lines to fit results into a middle end user screen
        {
            std::cout << std::endl;
        }
    }
    std::cout << " ]" << std::endl;
}

/**
 * Prints all the points generated for the TSP.
 * 
 * @param[in] cities the cities (points) generated for the TSP
 */
void print_cities(const std::array<std::pair<int, int>, N_POINTS> cities)
{
    for (int i = 0; i < N_POINTS; i += 1)
    {
        std::cout << std::setw(15) << "[POINT (" << i << ")]:\t" << std::setw(5) << cities.at(i).first << "\t" << std::setw(5) << cities.at(i).second << std::endl;
    }
    std::cout << std::endl << std::endl;
}

/*
 * Prints a given matrix row.
 * 
 * @param[in] r the matrix row
 * 
 * @note this function is called from print_matrx() function below
 */
void print_row(const std::array<double, N_POINTS>& r)
{
    for (auto const& element : std::as_const(r))
    {
        std::cout << std::setw(15) << element << " ";
    }
}

/**
 * Prints a given matrix.
 * 
 * @param[in] matrix the 2d array to print
 * @param[in] matrix_name the string that describes the matrix (ex. the name of the matrix)
 */
void print_matrix(const std::vector<std::array<double, N_POINTS>> matrix, const std::string matrix_name)
{
    std::cout << "Printing contents of \"" << matrix_name << "\"" << std::endl << "[";
    for (int col = 0; col < matrix.size(); col += 1)
    {
        print_row(matrix.at(col));
        std::cout << (col + 1 == matrix.size() ? "\t]" : "") << std::endl << " ";
    }
}

/**
 * Prints the TSP tour estimated by the ACS.
 * 
 * @param[in] tsp_route the precomputed TSP tour (route)
 */
void print_acs_tsp(const std::vector<int> tsp_route)
{
    std::cout << std::endl << "TSP Route optimized by ACS: " << std::endl << "[";
    for (auto const& node : std::as_const(tsp_route))
    {
        std::cout << std::setw(15) << node << (node == tsp_route.back() ? "\t]" : " ");
    }
    std::cout << std::endl;
}
