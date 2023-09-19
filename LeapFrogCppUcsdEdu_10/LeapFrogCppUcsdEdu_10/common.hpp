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
	static const int SAVE_TRAJECTORY;
	static const int SAVE_ENERGY;
	static const int TEMP_ADJUST_STEP;
	static const real DELTA_TEMP;

	static const int N;  // number of particles
	static const real BOX_SIZE; // size of the simulation box
	static const real MAX_VELOCITY;   // maximum initial velocity
	static const real R_CUTOFF;

	static const real DT;   // time step
	static const int N_STEPS;   // number of time steps
	static const real T0; // initial temperature in KB
	static const real TEMP_TARGET; // target temperature in KB

	static const std::string TRAJECTORY_FILE;
	static const std::string ENERGY_FILE;

	static const real TOLERANCE;
};



#endif // !COMMON_HPP