#include "communicator.hpp"

void Communicator::Init_comm(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int size;
    int dims[D2d] = {0, 0};
    int periods[D2d] = {0, 0};

    int reorder = true;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Dims_create(size, D2d, dims);

    MPI_Cart_create(MPI_COMM_WORLD, D2d, dims, periods, reorder, &(this->COMM_CART));
    // get my rank information
    MPI_Comm_rank(COMM_CART, &MY_RANK);
    MPI_Cart_coords(COMM_CART, MY_RANK, D2d, MY_COORD);
    // get my neighbours in x-direction
    MPI_Cart_shift(COMM_CART, 0, 1, &MY_NEIGHBOURS[LEFT], &MY_NEIGHBOURS[RIGHT]);
    // get my neighbours in y-direction
    MPI_Cart_shift(COMM_CART, 1, 1, &MY_NEIGHBOURS[BOTTOM], &MY_NEIGHBOURS[TOP]);

    this->DIMS[0] = dims[0];
    this->DIMS[1] = dims[1];

}

void Communicator::Print_RankInfo()
{
    cout << "[MPI Process " << MY_RANK << " ] ";
    cout << "in CART (" << MY_COORD[0] << ", " << MY_COORD[1] << ")" << endl;
}
void Communicator::Barrier()
{
    MPI_Barrier(COMM_CART);
}
/**
 * Waiting for implementation 
 */
void Communicator::SendRecv()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}