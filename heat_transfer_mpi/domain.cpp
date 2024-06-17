#include "domain.hpp"

void Domain::Init_bnd_type()
{
    // For top and bottom rows
    MPI_Type_contiguous(Ny, MPI_DOUBLE, &row_type);
    MPI_Type_commit(&row_type);
    // Fow left and right cols
    int count = Nx;
    int block_len = 1;
    int stride = Ny;
    MPI_Type_vector(count, block_len, stride, MPI_DOUBLE, &col_type);
    MPI_Type_commit(&col_type);
}

/**
 * Waiting for implementation
 */
void Domain::Exchange_Boundary(Communicator& comm)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void Domain::Print_Domain()
{
    int X_end = Nx + 2;
    int Y_end = Ny + 2;

    for(int i = 0; i < X_end; i++)
    {
        for(int j = 0; j < Y_end; j++)
        {
            std::cout << data[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
