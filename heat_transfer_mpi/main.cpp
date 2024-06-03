#include "parameters.hpp"
#include "communicator.hpp"

int MAX_STEPS = 1;

int main(int argc, char* argv[])
{
    
    Communicator MyComm(argc, argv);

    MyComm.Print_RankInfo();
    // wait until all processes finished data initialization
    // MPI_Barrier(COMM_CART);

    //     // copy data to send buf

    //     // exchange data with neighbours
    //     MPI_Sendrecv(SEND_BUF[UP], local_ny, MPI_DOUBLE, MY_NEIGHBOURS[UP], UP,
    //                     RECV_BUF[UP], local_ny, MPI_DOUBLE, MY_NEIGHBOURS[UP], DOWN, COMM_CART, &COMM_STAT);

    //     MPI_Sendrecv(SEND_BUF[DOWN], local_ny, MPI_DOUBLE, MY_NEIGHBOURS[DOWN], DOWN,
    //                     RECV_BUF[DOWN], local_ny, MPI_DOUBLE, MY_NEIGHBOURS[DOWN], UP, COMM_CART, &COMM_STAT);

    //     MPI_Sendrecv(SEND_BUF[LEFT], local_nx, MPI_DOUBLE, MY_NEIGHBOURS[LEFT], LEFT,
    //                     RECV_BUF[LEFT], local_nx, MPI_DOUBLE, MY_NEIGHBOURS[LEFT], RIGHT, COMM_CART, &COMM_STAT);

    //     MPI_Sendrecv(SEND_BUF[RIGHT], local_nx, MPI_DOUBLE, MY_NEIGHBOURS[RIGHT], RIGHT,
    //                     RECV_BUF[RIGHT], local_nx, MPI_DOUBLE, MY_NEIGHBOURS[RIGHT], LEFT, COMM_CART, &COMM_STAT);
    //     // copy data from recv_buf to halo fields 


    // delete buf
    return EXIT_SUCCESS;
}
