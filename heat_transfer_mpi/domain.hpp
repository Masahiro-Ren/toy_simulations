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
        Nx = GLOBAL_NX / dims[0];
        Ny = GLOBAL_NY / dims[1];

        NxA = Nx + 2;
        NyA = Ny + 2;

        Id = my_rank;
        
        data.resize(NxA, vec1d<double>(NyA, 0.0));

        Init_bnd_type();
    }

    ~Domain() {
        MPI_Type_free(&row_type);
        MPI_Type_free(&col_type);
    }


    double& operator()(const int& x, const int& y) { return data[x][y]; }

    void Exchange_Boundary(Communicator& comm);
    void Print_Domain();

private:
    vec2d<double> data;

    MPI_Datatype row_type;
    MPI_Datatype col_type;
    void Init_data(const int& my_rank, const int* my_neighbours);
    void Init_bnd_type();
};