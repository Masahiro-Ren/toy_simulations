#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template <typename T>
using vec1d = vector<T>;
template <typename T>
using vec2d = vector<vector<T>>;

/* --------- Parameters & variables ---------- */
constexpr int N = 102;

constexpr double X = 1.0; // real field size is 1 meter in X and Y directions
constexpr double delta = X / N;
constexpr int center = (int)(N/2);
const double e_zero = 8.85E-12;
const double CONV = 1.0E-6;

vec2d<double> phi;
vec2d<double> rho;

double MaxPhi;
double MaxErr;
double CurErr;
double Ex, Ey;


int main()
{
    /**
     * Initialization
    */
   int STEPS = 0;
   phi = vec2d<double>(N, vec1d<double>(N, 0.0));
   rho = vec2d<double>(N, vec1d<double>(N, 0.0));

   for(int i = 1; i < N - 1; i++)
   {
        for(int j = 0; j < N - 1; j++)
        {
            if( ((center - i) * (center - i) + (center - j) * (center - j) * delta * delta) < 0.05 * 0.05 )
                rho[i][j] = 1.0E-8;
        }
   }

   MaxPhi = 1.0E-10;

   /**
    * Simulation Start
   */

   while(MaxErr < CONV)
   {
        MaxErr = CurErr = 0.0;
        for(int i = 1; i < N - 1; i++)
        {
            for(int j = 1; j < N - 1; j++)
            {
                int Prev_phi = phi[i][j];
                phi[i][j] = ( phi[i + 1][j] +
                              phi[i][j + 1] +
                              phi[i - 1][j] +
                              phi[i][j - 1] +
                              rho[i][j] * delta * delta / e_zero
                             ) * 0.25;

                if(MaxPhi < std::abs(phi[i][j])) MaxPhi = phi[i][j];
                CurErr = (std::abs(phi[i][j] - Prev_phi)) / MaxPhi;
                if(MaxErr < CurErr) MaxErr = CurErr;
            }
        }
        STEPS++;
   }

   /**
    * Output & post process
    * TODO:
    * let the program output binary files
   */
   // Output phi here

   // Output electric here
   for(int i = 1; i < N - 1; i++)
   {
        for(int j = 1; j < N - 1; j++)
        {
            Ex = -(phi[i + 1][j] - phi[i - 1][j]) / ( 2.0 * delta );
            Ey = -(phi[i][j + 1] - phi[i][j - 1]) / ( 2.0 * delta );
            // file output
        }
   }

    return EXIT_SUCCESS;
}