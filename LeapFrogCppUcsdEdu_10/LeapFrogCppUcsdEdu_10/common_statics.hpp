#ifndef COMMON_STATIC_HPP
#define COMMON_STATIC_HPP
#include "common.hpp"


const real Constants::KB = 8.6173324e-5;
const real Constants::SIGMA = 0.369;
const real Constants::EPSILON = 1.19;

const real Constants::ATOMIC_MASS = 39.948;

const int Constants::N = 3;  // number of particles
const int Constants::N_STEPS = 10;   // number of time steps
const int Constants::SAVE_TRAJECTORY = 1;
const int Constants::SAVE_ENERGY = 1;
const int Constants::TEMP_ADJUST_STEP = 1;


const real Constants::BOX_SIZE = 6.0; // size of the simulation box
const real Constants::MAX_VELOCITY = 0.1;   // maximum initial velocity
const real Constants::DT = 0.01;   // time step
const real Constants::R_CUTOFF = 0.9;


const real Constants::T0 = 70.0 * KB; // initial temperature in KB
const real Constants::TEMP_TARGET = 300.0 * KB; // target temperature in KB
const real Constants::DELTA_TEMP = 50.00;

const std::string Constants::TRAJECTORY_FILE = "trajectory.txt";
const std::string Constants::ENERGY_FILE = "energy.txt";

const real Constants::TOLERANCE = 0.000000000001;

const real Constants::NEIGHBOR_RADIUS = 90;

#endif