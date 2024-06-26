#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>
#include <cstring>
#include <cstdlib>


// Parameters for Calculation
extern const double INIT_HI_TEMP;
extern const double INIT_LOW_TEMP;

extern const int GLOBAL_NX;
extern const int GLOBAL_NY;

extern const int D2d;

enum DIRECTIONS{BOTTOM, TOP, LEFT, RIGHT};
