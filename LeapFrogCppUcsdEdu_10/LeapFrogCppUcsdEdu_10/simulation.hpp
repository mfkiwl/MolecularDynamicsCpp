#ifndef SIM_HPP
#define SIM_HPP

#include "common.hpp"
#include "vec3.hpp"
#include "lennard_jones.hpp"
#include "particle.hpp"
#include "file_io.hpp"
#include "system.hpp"
#include "integrator.hpp"

class Simulation
{
private:
	System system_;
	EnergyData energyData_;

public:
	Simulation()
	{
		system_.dimension = Constants::BOX_SIZE;
		system_.epsilon = Constants::EPSILON;
		system_.kB = Constants::KB;
		system_.mass = Constants::ATOMIC_MASS;
		system_.sigma = Constants::SIGMA;
		system_.rCutOff = Constants::R_CUTOFF;
		system_.neighRadius = Constants::NEIGHBOR_RADIUS;

		system_.initialize(Constants::N, Constants::T0);

		FileIO::clearFile(Constants::TRAJECTORY_FILE);
		FileIO::clearFile(Constants::ENERGY_FILE);
	}

	void run()
	{
		// Run the simulation
		for (int step = 0; step < Constants::N_STEPS; step++)
		{
			std::cout << "Step : " << step << std::endl;

			Integrator::Lepfrog(system_.getParticles(), Constants::DT);

			FileIO::writeTrajectoryToFile(Constants::TRAJECTORY_FILE, system_.getParticles());
			
			EnergyData data = system_.computeEnergy(step);

			energyData_.update(data);

			FileIO::writeEnergyToFile(Constants::ENERGY_FILE, energyData_);

			////system_.scaleTemperature(Constants::DELTA_TEMP);

			system_.buildNeighborList();
		}

		std::cout << "\n\n\nSimulation is complete!" << std::endl;
	}
};

#endif // !SIM_SYSTEM_HPP