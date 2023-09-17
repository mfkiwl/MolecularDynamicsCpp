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
	static const real DT;   // time step
	static const int N_STEPS;   // number of time steps
	static const real T0; // initial temperature in KB
	static const real TEMP_TARGET; // target temperature in KB

	static const std::string TRAJECTORY_FILE;
	static const std::string ENERGY_FILE;

	static const real TOLERANCE;
};

const real Constants::KB = 8.6173324e-5;
const real Constants::SIGMA = 0.369;
const real Constants::EPSILON = 1.19;

const real Constants::ATOMIC_MASS = 39.948;

const int Constants::N = 9;  // number of particles
const int Constants::N_STEPS = 100;   // number of time steps
const int Constants::SAVE_TRAJECTORY = 2;
const int Constants::SAVE_ENERGY = 2;
const int Constants::TEMP_ADJUST_STEP = 2;

const real Constants::BOX_SIZE = 6.0; // size of the simulation box
const real Constants::MAX_VELOCITY = 0.1;   // maximum initial velocity
const real Constants::DT = 0.01;   // time step

const real Constants::T0 = 70.0 * KB; // initial temperature in KB
const real Constants::TEMP_TARGET = 300.0 * KB; // target temperature in KB
const real Constants::DELTA_TEMP = 50.00;

const std::string Constants::TRAJECTORY_FILE = "trajectory.txt";
const std::string Constants::ENERGY_FILE = "energy.txt";

const real Constants::TOLERANCE = 0.000000000001;

#endif // !COMMON_HPP