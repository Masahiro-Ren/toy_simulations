#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template <typename T>
using vec1d = vector<T>;
template <typename T>
using vec2d = vector<vector<T>>;

/* --------- Parameters & variables ---------- */
constexpr int NX = 100;

constexpr double X = 1.0; // real field size is 1 meter in X and Y directions
constexpr double dx = X / NX;
const double e_zero = 8.85E-12;
const double CONV = 1.0E-6;


int main()
{
    return EXIT_SUCCESS;
}