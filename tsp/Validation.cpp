
#include "Validation.h"

/**
 * Exports nodes of the computed TSP route to CSV file.
 * 
 * @param[in] cities the vector with the ordered cities that is to be exported
 * @param[in] filename the name of the CSV file
 * 
 * @note this function is called by:
 *          - the Naive TSP algorithm
 *          - the Naive TSP algorithm (Parallel Implementation)
 *          - the TSP with nearest neighbor algorithm
 *          - the TSP with naive nearest neighbor algorithm
 *          - the TSP with naive nearest neighbor algorithm (Parallel Implementation)
 * 
 * @note for the module to work, there must exist a directory called data with the same parent
 *      directory with the project. If you want to store the data to a custom directory, then
 *      change the proper line of code.
 */
void export_graph_newtork_array(const std::array<std::pair<int, int>, N_POINTS> cities, std::string filename)
{
    std::ofstream export_stream;
    export_stream.open("./data/" + filename + ".csv");      /// If you want to store the data into a different directory change "./data/" to whatever you want
    for (int i = 0; i < cities.size(); i += 1)
    {
        export_stream << cities.at(i).first << "," << cities.at(i).second << std::endl;
    }
    export_stream.close();
}

/**
 * Exports nodes of the computed TSP route to CSV file.
 * 
 * @param[in] cities the container that holds the dataset
 * @param[in] filename the name of the CSV file
 * @param[in] tsp_route the container with the ordered indexes of `cities` computed by the ACS to be exported
 * 
 * @note this function is called by:
 *          - the ACS TSP algorithm
 *          - the ACS TSP algorithm (Parallel Implementation)
 * 
 * @note for the module to work, there must exist a directory called data with the same parent
 *      directory with the project. If you want to store the data to a custom directory, then
 *      change the proper line of code.
 */
void export_acs_tsp_route(const std::array<std::pair<int, int>, N_POINTS> cities, std::string filename, const std::vector<int> tsp_route)
{
    std::ofstream export_stream;
    export_stream.open("./data/" + filename + ".csv");      /// If you want to store the data into a different directory change "./data/" to whatever you want
    for (int i = 0; i < tsp_route.size(); i += 1)
    {
        export_stream << cities.at(tsp_route.at(i)).first << "," << cities.at(tsp_route.at(i)).second << std::endl;
    }
    export_stream.close();
}
