#ifndef COMMON_STATIC_HPP
#define COMMON_STATIC_HPP
#include "common.hpp"

const real Constants::KB = 8.6173324e-5;
const real Constants::SIGMA = 0.369;
const real Constants::EPSILON = 1.19;

const real Constants::ATOMIC_MASS = 39.948;

const int Constants::N_PARTICLES = 3;  // number of particles
const int Constants::N_STEPS = 10;   // simulation iterations
const int Constants::TRAJEC_WRITE_FREQ = 1;
const int Constants::ENERGY_WRITE_FREQ = 1;
const int Constants::ADJUST_TMPTR_FREQ = 1;

const real Constants::SIM_BOX_DIM = 6.0; // dimension of the simulation box
const real Constants::MAX_VELOCITY = 0.1; // maximum initial velocity
const real Constants::DELTA_TIME = 0.01; // time step
const real Constants::R_CUTOFF = 0.9;
const real Constants::NEIGHBOR_RADIUS = 90;

const real Constants::INIT_TEMPTR = 70.0 * KB; // initial temperature in KB
const real Constants::TRGT_TEMPTR = 300.0 * KB; // target temperature in KB
const real Constants::DLTA_TEMPTR = 50.00;

const std::string Constants::TRAJECTORY_FILE = "trajectory.txt";
const std::string Constants::ENERGY_FILE = "energy.txt";

const real Constants::UNIT_TEST_TOLERANCE = 0.000000000001;
#endif