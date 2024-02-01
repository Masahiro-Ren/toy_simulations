#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <random>

using namespace std;

template <typename T>
using vec1d = vector<T>;
template <typename T>
using vec2d = vector<vector<T>>;

enum COORD{X, Y};

constexpr static int DIM = 2;
constexpr static int N = 100;
constexpr static double G = 6.67e-11; 
constexpr static double dt = 0.01;
// Let's say the total mass of particles is 20
constexpr static double M = 20.0;
/**
 *  gravitational softening, which is a trick for paticle simulation to 
 *  avoid too close encounter that would result in unrealistic motion 
 * */
constexpr static double softening = 0.1;
// max time steps
constexpr static int TIME_STEPS = 100;

vec2d<double> pos;
vec2d<double> vel;
vec2d<double> acc;
vec1d<double> mass;

void init();
void kick();
void drift();
void cal_acc();

int main()
{
    double T = 0.0;
    init();
    // ================== Simulation Start =================
    /**
     * Leap frog integration:
     * kick-drift-acc-kick 
    */
    for(int step = 0; step < TIME_STEPS; step++)
    {
        // update velocity 1/2 time kick
        kick();
        // drift
        drift();
        // calculate accelerations
        cal_acc();
        // update velocity another 1/2 time kick
        kick();
        // update time
        T += dt;
        // calculate energy

    }


    return 0;
}


void init()
{
    pos = vec2d<double>(DIM, vec1d<double>(N));
    vel = vec2d<double>(DIM, vec1d<double>(N));
    acc = vec2d<double>(DIM, vec1d<double>(N));
    mass = vec1d<double>(N, (M / double(N)));

    // initialize random engine
    std::random_device rnd;
    std::mt19937_64 rng(rnd());
    std::uniform_real_distribution<double> get_rand(0.0, 1.0);

    for(int i = 0; i < N; i++)
    {
        // init position
        pos[X][i] = get_rand(rng);
        pos[Y][i] = get_rand(rng);
        // init velocity
        vel[X][i] = get_rand(rng);
        vel[Y][i] = get_rand(rng);
    }

    // Convert to Center-of-Mass frame ???

    // Calculate init acceleration
    cal_acc();
}

void cal_acc()
{
    // Calculate init acc for each particle
    for(int i = 0; i < N; i++)
    {
        acc[X][i] = 0;
        acc[Y][i] = 0;
        for(int j = 0; j < N; j++)
        {
            if(i == j) continue;

            double dx = pos[X][i] - pos[X][j];
            double dy = pos[Y][i] - pos[Y][j];

            double r = sqrt(dx * dx + dy * dy + softening * softening);
            double ir3 = 1.0 / (r * r * r);

            acc[X][i] -= G * mass[j] * dx * ir3;
            acc[Y][i] -= G * mass[j] * dy * ir3;
        }
    }
}

void kick()
{
    for(int i = 0; i < N; i++)
    {
        vel[X][i] += acc[X][i] * dt / 2.0;
        vel[Y][i] += acc[Y][i] * dt / 2.0;
    }
}

void drift()
{
    for(int i = 0; i < N; i++)
    {
        pos[X][i] += vel[X][i] * dt;
        pos[Y][i] += vel[Y][i] * dt;
    }
}