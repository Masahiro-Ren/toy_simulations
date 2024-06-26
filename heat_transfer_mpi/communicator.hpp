#pragma once

#include "parameters.hpp"

class Communicator {
public:
    MPI_Comm COMM_CART;
    MPI_Status COMM_STAT;
    int DIMS[2];
    int MY_RANK;
    int MY_COORD[2];
    int MY_NEIGHBOURS[4];

    Communicator(int argc, char* argv[])
    {
        // cout << "Initializing mpi process... \n";
        Init_comm(argc, argv);
    }

    ~Communicator() 
    { 
        // cout << "Ending mpi process... \n";
        MPI_Finalize(); 
    }

    void Print_RankInfo();
    void Barrier();
    void SendRecv(double* send_pos, int send_cnt, 
                  double* recv_pos, int recv_cnt, 
                  int max_direction, int min_direction, MPI_Datatype data_type);

private:
    void Init_comm(int argc, char* argv[]);
};