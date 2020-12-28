
#include "Pherormone.h"

/**
 * Initializes a matrix.
 * 
 * @param[in, out] pherormone_matrix the matrix given for initialization
 * 
 * @note this is used to initialize the pherormone matrix
 */
void initialize_pherormone_matrix(std::vector<std::array<double, N_POINTS>>& pherormone_matrix)
{
    for (int i = 0; i < N_POINTS; i += 1)
    {
        pherormone_matrix.at(i).fill(1.0);      /// Fill the `i`-th row of the matrix with ones. That way all nodes have an equal chance to be selected by any ant.
        pherormone_matrix.at(i).at(i) = 0.0;    /// Change the diagonal element to zero. That way we reinforce the ants not to chose the same node.
    }
}
