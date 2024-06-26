#include "domain.hpp"

void Domain::Init_bnd_type()
{
    // For top and bottom rows
    MPI_Type_contiguous(Ny, MPI_DOUBLE, &row_type);
    MPI_Type_commit(&row_type);
    // Fow left and right cols
    int count = Nx;
    int block_len = 1;
    int stride = NyA;
    MPI_Type_vector(count, block_len, stride, MPI_DOUBLE, &col_type);
    MPI_Type_commit(&col_type);
}

void Domain::Replicate_Data(double* dst)
{
    size_t bytes = NxA * NyA * sizeof(double);
    std::memcpy(dst, data, bytes);
}

void Domain::Assign(double* src)
{
    size_t bytes = NxA * NyA * sizeof(double);
    std::memcpy(data, src, bytes);
}

int Domain::Get_index(const int& x, const int& y)
{
    return x * NyA + y;
}

/**
 * Waiting for implementation
 */
void Domain::Exchange_Boundary(Communicator& comm)
{
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    int send_idx, recv_idx;
    /**
     * Send my top row to the top domain
     * Update bottom guard row from the bottom domain
     * */
    send_idx = Get_index(1, 1);
    recv_idx = Get_index(Nx+1, 1);
    comm.SendRecv(&data[send_idx], 1, 
                  &data[recv_idx], 1, 
                  TOP, BOTTOM, row_type);
    /**
     * Send my bottom row to the bottom domain
     * Updata my top guard row from the top domain
     * */
    send_idx = Get_index(Nx, 1);
    recv_idx = Get_index(0, 1);
    comm.SendRecv(&data[send_idx], 1, 
                  &data[recv_idx], 1, 
                  BOTTOM, TOP, row_type);
    /**
     * Send my left column to the left domain
     * Update right guard column from the right domain
     * */
    send_idx = Get_index(1,1);
    recv_idx = Get_index(1, Ny + 1);
    comm.SendRecv(&data[send_idx], 1, 
                  &data[recv_idx], 1, 
                  LEFT, RIGHT, col_type);
    /**
     * Send my right column to the right domain
     * Update left guard column from the left domain
     * */
    send_idx = Get_index(1,Ny);
    recv_idx = Get_index(1, 0);
    comm.SendRecv(&data[send_idx], 1, 
                  &data[recv_idx], 1, 
                  RIGHT, LEFT, col_type);
}

void Domain::Print_Domain()
{

    for(int i = 0; i < NxA; i++)
    {
        for(int j = 0; j < NyA; j++)
        {
            // std::cout << data[i * NyA + j] << "\t";
            printf("%.4f\t", data[i * NyA + j]);
        }
        // std::cout << std::endl;
        printf("\n");
    }
}
