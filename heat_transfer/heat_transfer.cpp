#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
using vec1d = vector<T>;

template <typename T>
using vec2d = vector<vector<T>>;

/**
 * NOTE : The 1st and last grid cells of each direction are boundary conditions.
 *        So that the real grid size is acutually 10 x 10.
*/
const int NX = 12;
const int NY = 12;
const int TIME_STEPS = 50;

const double INIT_HI_TEMP = 10.0;
const double INIT_MID_TEMP = 5.5;
const double INIT_LOW_TEMP = 1.0;

/**
 * A rough real-time visualization of the heat transfer 
*/
void display(vec2d<double>& T);

int main()
{   
    /* =================== Initialize ================== */
    vec2d<double> T(NX, vec1d<double>(NY, INIT_MID_TEMP));
    vec2d<double> nT(NX, vec1d<double>(NY));
    
    // Set up boundary conditions
    for(int i = 0; i < NX; i++)
    {
        T[i][0] = INIT_LOW_TEMP;
        T[i][NY - 1] = INIT_HI_TEMP;
    }
    for(int j = 0; j < NY; j++)
    {
        T[0][j] = INIT_HI_TEMP;
        T[NX - 1][j] = INIT_LOW_TEMP;
    }

    std::copy(T.begin(), T.end(), nT.begin());
    /* ================ Initialize done =============== */

    /* ============== Heat transfer start ============= */
    for(int istep = 0; istep < TIME_STEPS; istep++)
    {
        // The kernel of heat transfer
        for(int ix = 1; ix < NX - 1; ix++)
        {
            for(int iy = 1; iy < NY - 1; iy++)
            {
                nT[ix][iy] = 0.25 * (  T[ix + 1][iy] +
                                       T[ix][iy + 1] +
                                       T[ix - 1][iy] +
                                       T[ix][iy - 1] );
            }
        }

        // copy the new result
        std::copy(nT.begin(), nT.end(), T.begin());

        // display every 5 steps
        if(istep % 5 == 0)
        {
            display(T);
        }
    }
    /* ============== Heat transfer end ============= */

    return EXIT_SUCCESS;
}

void display(vec2d<double>& T)
{
    string color[5] = { "\x01B[34m", "\x01B[39m", "\x01B[31m" };
    string pixels = "*.+";
    int NPIX = pixels.size();

    for(int ix = 0; ix < NX; ix++)
    {
        for(int iy = 0; iy < NY; iy++)
        {
            int index = static_cast<int>( T[ix][iy] / 10.0 * (double)(NPIX - 1) + 0.5 );
            cout << color[index] << pixels[index] << " ";
        }
        cout << endl;
    }

    // reset terminal color
    cout << "\x01B[39m" << endl;
}
