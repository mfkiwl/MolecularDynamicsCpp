#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <iostream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

typedef double real;

class Constants 
{
public:
	static const real KB;
	static const real EPSILON;
	static const real SIGMA;
	static const real ATOMIC_MASS;
	static const int SAVE_TRAJECTORY_FREQ;
	static const int SAVE_ENERGY_FREQ;
	static const int ADJUST_TEMP_FREQ;
	static const real DELTA_TEMP;

	static const int N_PARTICLES;  // number of particles
	static const real SIM_BOX_DIMENSION; // size of the simulation box
	static const real MAX_VELOCITY;   // maximum initial velocity
	static const real R_CUTOFF;

	static const real DELTA_TIME;   // time step
	static const int N_STEPS;   // number of time steps
	static const real INIT_TEMPTR; // initial temperature in KB
	static const real TARGET_TEMPTR; // target temperature in KB

	static const std::string TRAJECTORY_FILE;
	static const std::string ENERGY_FILE;

	static const real UNIT_TEST_TOLERANCE;

	static const real NEIGHBOR_RADIUS;
};

#endif // !COMMON_HPP