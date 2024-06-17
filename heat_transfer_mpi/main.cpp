#include "parameters.hpp"
#include "communicator.hpp"
#include "domain.hpp"

int MAX_STEPS = 1;

void Init_Data(Communicator& MyComm, Domain& MyDomain);

int main(int argc, char* argv[])
{
    
    Communicator MyComm(argc, argv);
    MyComm.Print_RankInfo();
    Domain MyDomain(MyComm.DIMS, MyComm.MY_RANK);

    Init_Data(MyComm, MyDomain);
    // wait until all processes finished data initialization
    MyComm.Barrier();

    if(MyDomain.Id == 1)
    {
        MyDomain.Print_Domain();
    }

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


    return EXIT_SUCCESS;
}

void Init_Data(Communicator& MyComm, Domain& MyDomain)
{
    if(MyComm.MY_NEIGHBOURS[TOP] == MPI_PROC_NULL)
    {
        for(int y = 0; y < MyDomain.NyA; y++)
        {
            MyDomain(0, y) = INIT_HI_TEMP;
        }
    }

    if(MyComm.MY_NEIGHBOURS[BOTTOM] == MPI_PROC_NULL)
    {
        for(int y = 0; y < MyDomain.NyA; y++)
        {
            MyDomain(MyDomain.NxA - 1, y) = INIT_LOW_TEMP;
        }
    }

    if(MyComm.MY_NEIGHBOURS[LEFT] == MPI_PROC_NULL)
    {
        for(int x = 0; x < MyDomain.NxA; x++)
        {
            MyDomain(x, 0) = INIT_LOW_TEMP;
        }
    }

    if(MyComm.MY_NEIGHBOURS[RIGHT] == MPI_PROC_NULL)
    {
        for(int x = 0; x < MyDomain.NxA; x++)
        {
            MyDomain(x, MyDomain.NyA - 1) = INIT_HI_TEMP;
        }
    }
}