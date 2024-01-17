#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

template <typename T>
using vec1d = vector<T>;
template <typename T>
using vec2d = vector<vector<T>>;

/* --------- Parameters & variables ---------- */
constexpr int Ntot = 102;
constexpr int N = 100;

constexpr double X = 1.0; // real field size is 1 meter in X and Y directions
constexpr double delta = X / N;
constexpr int center = (int)(N/2);
const double e_zero = 8.85e-12;
const double CONV = 1.0e-6;

vec2d<double> phi;
vec2d<double> rho;

double MaxPhi;
double MaxErr;
double CurErr;

int main()
{
    /**
     * Initialization
    */
   int STEPS = 0;
   MaxPhi = 1.0e-10;

   phi = vec2d<double>(Ntot, vec1d<double>(Ntot, 0.0));
   rho = vec2d<double>(Ntot, vec1d<double>(Ntot, 0.0));

   for(int i = 1; i <= N; i++)
   {
        for(int j = 1; j <= N; j++)
        {
            if( ((center - i) * (center - i) + (center - j) * (center - j)) * delta * delta < 0.05 * 0.05 )
                rho[i][j] = 1.0e-8;
        }
   }

   /**
    * Simulation Start
   */

   do
   {
        if(!(STEPS%1000)) cout << "Steps " << STEPS << ". MaxErr=" << MaxErr << "; MaxPhi=" << MaxPhi << endl;
        MaxErr = CurErr = 0.0;
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= N; j++)
            {
                double Prev_phi = phi[i][j];

                phi[i][j] = ( phi[i + 1][j] +
                              phi[i - 1][j] +
                              phi[i][j + 1] +
                              phi[i][j - 1] +
                              rho[i][j] * delta * delta / e_zero 
                             ) * 0.25;

                if(MaxPhi < fabs(phi[i][j])) MaxPhi = phi[i][j];

                CurErr = (fabs(phi[i][j] - Prev_phi)) / MaxPhi;

                if(MaxErr < CurErr) MaxErr = CurErr;
            }
        }
        STEPS++;
    } while(MaxErr > CONV);

   /**
    * Output & post process
   */
   // Output phi here
   ofstream phi_out("phi.avd", ios::binary);
   for(int i = 1; i <= N; i++)
   {
        for(int j = 1; j <= N; j++)
        {
            phi_out.write(reinterpret_cast<const char*>(&phi[i][j]), sizeof(double));
        }
   }
   phi_out.close();

   // Output electric here
   ofstream elec_out("electric.avd", ios::binary);
   for(int i = 1; i <= N; i++)
   {
        for(int j = 1; j <= N; j++)
        {
            double Ex = -(phi[i + 1][j] - phi[i - 1][j]) / ( 2.0 * delta );
            double Ey = -(phi[i][j + 1] - phi[i][j - 1]) / ( 2.0 * delta );
            double Esqrt = std::sqrt(Ex * Ex + Ey * Ey);

            elec_out.write(reinterpret_cast<const char*>(&Ex), sizeof(double));
            elec_out.write(reinterpret_cast<const char*>(&Ey), sizeof(double));
            elec_out.write(reinterpret_cast<const char*>(&Esqrt), sizeof(double));
        }
   }
   elec_out.close();

    return EXIT_SUCCESS;
}