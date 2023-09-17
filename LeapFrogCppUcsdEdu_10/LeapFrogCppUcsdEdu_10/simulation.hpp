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

public:
	Simulation()
	{
		system_.dimension = Constants::BOX_SIZE;
		system_.epsilon = Constants::EPSILON;
		system_.kB = Constants::KB;
		system_.mass = Constants::ATOMIC_MASS;
		system_.sigma = Constants::SIGMA;
		system_.Initialize(Constants::T0);

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

			// Save the trajectory every 100 steps
			//if (step % Constants::SAVE_TRAJECTORY == 0)
			//{
				FileIO::writeTrajectoryToFile(Constants::TRAJECTORY_FILE, system_.getParticles());
			//}

			//if (step % Constants::SAVE_ENERGY == 0)
			{
				system_.computeEnergy();

				EnergyData energy;
				energy.step_no = step;
				energy.Kinetic_engy = system_.getKineticEnergy();
				energy.Poten_energy = system_.getPotentialEnergy();
				energy.TotalEnergy = system_.getTotalEnergy();
				energy.Pot_engy_attractive = system_.getPotentialEnergyAttractive();
				energy.Pot_engy_repulsive = system_.getPotentialEnergyRepulsive();
				energy.step_no = step;
				energy.Pot_engy_balloon = 0;

				FileIO::writeEnergyToFile(Constants::ENERGY_FILE, energy);
			}

			// Adjust the temperature every `X` steps
			//if (step % Constants::TEMP_ADJUST_STEP == 0)
			//{
			//	// Calculate the current temperature
				
			//
			//	// Adjust the temperature
				system_.setTemperature(Constants::DELTA_TEMP);
			//}
		}

		std::cout << "\n\n\nSimulation is complete!" << std::endl;
	}
};

#endif // !SIM_SYSTEM_HPP