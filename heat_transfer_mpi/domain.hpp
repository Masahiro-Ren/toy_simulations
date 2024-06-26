#pragma once

#include "parameters.hpp"
#include "communicator.hpp"

class Domain {
public:
    int Id;
    int Nx, Ny;
    int NxA, NyA;

    Domain(const int* dims, const int& my_rank) 
    {
        /**
         * For arbitrary sizes and processes ??
         * 
         * if(MY_COORD[0] == dims[0] - 1)
         * {
         *      residual = GLOBAL_NX % dims[0];
         *      Nx = (residual != 0) ? residual : GLOBAL_NX / dims[0];
         * }
         * else
         * {
         *      Nx = GLOBAL_NX / dims[0];
         * }
         * 
         * Ny is same as Nx
         */
        Nx = GLOBAL_NX / dims[0];
        Ny = GLOBAL_NY / dims[1];

        NxA = Nx + 2;
        NyA = Ny + 2;

        Id = my_rank;
        
        data = new double[NxA * NyA];

        std::memset(data, 0, NxA * NyA * sizeof(double));

        Init_bnd_type();
    }

    ~Domain() {
        MPI_Type_free(&row_type);
        MPI_Type_free(&col_type);
        delete[] data;
    }


    double& operator()(const int& x, const int& y) { return data[x * NyA + y]; }

    void Replicate_Data(double* dst);
    void Assign(double* src);
    void Exchange_Boundary(Communicator& comm);
    void Print_Domain();

private:
    double* data;

    MPI_Datatype row_type;
    MPI_Datatype col_type;
    void Init_data(const int& my_rank, const int* my_neighbours);
    void Init_bnd_type();
    int Get_index(const int& x, const int& y);
};