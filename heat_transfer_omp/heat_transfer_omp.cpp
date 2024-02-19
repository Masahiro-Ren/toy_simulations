#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

using namespace std;

template <typename T>
using vec1d = vector<T>; 

template <typename T>
using vec2d = vector<vector<T>>;


const int Nxtot = 102;
const int Nytot = 102;

const int Nx = 100;
const int Ny = 100;

const double INIT_HI_TEMP = 100.0;
const double INIT_LOW_TEMP = 1.0;

const int TIME_STEPS = 100;

void kernel(vec2d<double>& T)
{
    vec2d<double> nT(Nxtot, vec1d<double>(Nytot));

    int istep, ix, iy;
    
    /* ============ Heat transfer start ============== */
    #pragma omp parallel private(istep, ix, iy)
    {
        for(istep = 0; istep < TIME_STEPS; istep++)
        {
            // copy value to T from last time step
            #pragma omp for
            for(ix = 0; ix < Nxtot; ix++)
            {
                for(int iy = 0; iy < Nytot; iy++)
                {
                    nT[ix][iy] = T[ix][iy];
                }
            }

            #pragma omp for
            for(ix = 1; ix <= Nx; ix++)
            {
                for( iy = 1; iy <= Ny; iy++)
                {
                    T[ix][iy] = 0.25 * (nT[ix + 1][iy] +
                                        nT[ix - 1][iy] +
                                        nT[ix][iy + 1] +
                                        nT[ix][iy - 1]);
                }
            }
        }
    }
}

void output(vec2d<double>& data)
{   
    ofstream file("heat.dat", ios::binary);

    for(int ix = 0; ix < Nxtot; ix++)
    {
        for(int iy = 0; iy < Nytot; iy++)
        {
            file.write(reinterpret_cast<const char*>(&data[ix][iy]), sizeof(double));
        }
    }

    file.close();
}

int main()
{
    double MID_TEMP = (INIT_HI_TEMP + INIT_LOW_TEMP) / 2.0;
    vec2d<double> T(Nxtot, vec1d<double>(Nytot));
    // Initialize T
    // Avoid first-touch issue on ccNUMA computer 
    #pragma omp parallel for private(j)
    for(int i = 0; i < Nxtot; i++)
    {
        for(int j = 0; j < Nytot; j++)
        {
            T[i][j] = MID_TEMP;
        }
    }

    #pragma omp parallel for
    for(int i = 0; i < Nxtot; i++)
    {
        T[i][0] = INIT_LOW_TEMP;
        T[i][Nytot - 1] = INIT_HI_TEMP;
    }

    #pragma omp parallel for
    for(int j = 0; j < Nytot; j++)
    {
        T[0][j] = INIT_HI_TEMP;
        T[Nxtot - 1][j] = INIT_LOW_TEMP;
    }

    // Start simulation
    double st_time = omp_get_wtime();
    kernel(T);
    double ed_time = omp_get_wtime();

    cout << "Execution Time : " << ed_time - st_time << endl;

    // Output result
    output(T);

    return 0;
}