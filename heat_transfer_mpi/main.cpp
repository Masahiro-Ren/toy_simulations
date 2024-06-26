#include "parameters.hpp"
#include "communicator.hpp"
#include "domain.hpp"

int MAX_STEPS = 200;

void Init_Data(Communicator& MyComm, Domain& MyDomain);

int main(int argc, char* argv[])
{
    
    Communicator MyComm(argc, argv);
    Domain MyDomain(MyComm.DIMS, MyComm.MY_RANK);

    // wait until all processes finished data initialization
    Init_Data(MyComm, MyDomain);
    MyComm.Barrier();

    double* temp = new double[MyDomain.NxA * MyDomain.NyA];
    MyDomain.Replicate_Data(temp);

    // Calculation
    for(int istep = 0; istep < MAX_STEPS; istep++)
    {
        for(int ix = 1; ix <= MyDomain.Nx; ix++)
        {
            for(int iy = 1; iy <= MyDomain.Ny; iy++)
            {
                temp[ix * MyDomain.NyA + iy] = 0.25 * ( MyDomain(ix + 1, iy) +
                                                        MyDomain(ix - 1, iy) +
                                                        MyDomain(ix, iy + 1) +
                                                        MyDomain(ix, iy - 1)  );
            }
        }

        MyDomain.Assign(temp);

        // Communication
        MyDomain.Exchange_Boundary(MyComm);
    }

    MyComm.Barrier();

    // if(MyDomain.Id == 0)
    // {
    //     MyComm.Print_RankInfo();
    //     MyDomain.Print_Domain();
    // }

    delete[] temp;
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