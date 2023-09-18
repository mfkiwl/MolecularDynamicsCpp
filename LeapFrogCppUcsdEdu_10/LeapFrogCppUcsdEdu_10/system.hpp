#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "common.hpp"
#include "vec3.hpp"
#include "lennard_jones.hpp"
#include "particle.hpp"
#include "file_io.hpp"

class System
{
private:
	Vec3 totalAcceleration_;
	real totalPotentialEnergyRepulsive_;
	real totalPotentialEnergyAttractive_;
	real totalPotentialEnergy_;
	real totalKineticEnergy_;
	real totalEnergy_;
	real currentTemperature_;

public:
	

private:
	int particleCount_;
	std::vector<Particle> particles_;

public:
	int getParticlesCount()
	{
		return particleCount_;
	}

public:
	real dimension;
	real sigma;
	real epsilon;
	real mass;
	real kB;
	real rCutOff;

	System()
	{
		totalAcceleration_.x = 0; totalAcceleration_.y = 0; totalAcceleration_.z = 0;
		totalPotentialEnergyRepulsive_ = 0.0;
		totalPotentialEnergyAttractive_ = 0.0;
		totalPotentialEnergy_ = 0.0;
		totalKineticEnergy_ = 0.0;
		totalEnergy_ = 0.0;
		currentTemperature_ = 0.0;

		particleCount_ = 0;

		dimension = 0;
		sigma = 0;
		epsilon = 0;
		mass = 0;
		kB = 0;
		rCutOff = 0;
	}

	System(real sigma, real epsilon, real mass, real kB, real dimension, real rCutOff): 
		sigma(sigma), epsilon(epsilon), mass(mass), kB(kB), dimension(dimension), rCutOff(rCutOff)
	{
		totalAcceleration_.x = 0; totalAcceleration_.y = 0; totalAcceleration_.z = 0;
		totalPotentialEnergyRepulsive_ = 0.0;
		totalPotentialEnergyAttractive_ = 0.0;
		totalPotentialEnergy_ = 0.0;
		totalKineticEnergy_ = 0.0;
		totalEnergy_ = 0.0;
		currentTemperature_ = 0.0;

		particleCount_ = 0;
	}

	void setTemperature(real deltaTemperature)
	{
		real currentTemperature = currentTemperature_;
		real targetTemperature = currentTemperature + deltaTemperature;

		for (auto& particle : particles_)
		{
			particle.setTemperature(targetTemperature);
		}
	}

	std::vector<Particle>& getParticles()
	{
		return particles_;
	}

	EnergyData computeEnergy()
	{
		int n_particles = particles_.size();
		int n_interactions = (n_particles * (n_particles - 1)) / 2;

		double sumTotalEnergy = 0.0;
		double sumSquaredTotalEnergy = 0.0;
		double sumKineticEnergy = 0.0;
		double sumSquaredKineticEnergy = 0.0;
		double sumPotentialEnergy = 0.0;
		double sumSquaredPotentialEnergy = 0.0;

		for (size_t i = 0; i < n_particles; i++)
		{
			Vec3 particleAcceleration(0.0, 0.0, 0.0);

			const Particle& particle = particles_[i];

			for (size_t j = i + 1; j < n_particles; j++)
			{
				const Particle& other = particles_[j];

				// Calculate total energy for the particle
				double totalEnergy = particle.getTotalEnergy(other);

				// Calculate kinetic energy for the particle
				double kineticEnergy = particle.getKineticEnergy();

				// Calculate potential energy for the particle
				double potentialEnergy = particle.getPotentialEnergy(other);

				// Sum up the energies
				sumTotalEnergy += totalEnergy;
				sumSquaredTotalEnergy += totalEnergy * totalEnergy;
				sumKineticEnergy += kineticEnergy;
				sumSquaredKineticEnergy += kineticEnergy * kineticEnergy;
				sumPotentialEnergy += potentialEnergy;
				sumSquaredPotentialEnergy += potentialEnergy * potentialEnergy;
			}
		}

		// Calculate mean values
		double meanTotalEnergy = sumTotalEnergy / n_interactions;
		double meanKineticEnergy = sumKineticEnergy / n_interactions;
		double meanPotentialEnergy = sumPotentialEnergy / n_interactions;

		// Calculate variances
		double varianceTotalEnergy = (sumSquaredTotalEnergy / n_interactions) - (meanTotalEnergy * meanTotalEnergy);
		double varianceKineticEnergy = (sumSquaredKineticEnergy / n_interactions) - (meanKineticEnergy * meanKineticEnergy);
		double variancePotentialEnergy = (sumSquaredPotentialEnergy / n_interactions) - (meanPotentialEnergy * meanPotentialEnergy);

		// Calculate standard deviations
		double stdDevTotalEnergy = std::sqrt(varianceTotalEnergy);
		double stdDevKineticEnergy = std::sqrt(varianceKineticEnergy);
		double stdDevPotentialEnergy = std::sqrt(variancePotentialEnergy);

		EnergyData energyData;
		energyData.TotalEnergyMean = meanTotalEnergy;
		energyData.TotalEnergyVariance = varianceTotalEnergy;
		energyData.TotalEnergyStdDev = stdDevTotalEnergy;
		energyData.KineticEngyMean = meanKineticEnergy;
		energyData.KineticEngyVariance = varianceKineticEnergy;
		energyData.KineticEngyStdDev = stdDevKineticEnergy;
		energyData.PotenEnergyMean = meanPotentialEnergy;
		energyData.PotenEnergyVariance = variancePotentialEnergy;
		energyData.PotenEnergyStdDev = stdDevPotentialEnergy;

		return energyData;
	}

	/*
	void Initialize(real T0)
	{
		const real a = sigma / 2.0; // Length unit a determined by σ = 2a

		const real cellPositions[4][3] = {
												{ 0.5 * a, 0.5 * a, 0.5 * a },
												{ 0.5 * a, 1.5 * a, 1.5 * a },
												{ 1.5 * a, 0.5 * a, 1.5 * a },
												{ 1.5 * a, 1.5 * a, 0.5 * a }
											};

		const real cellShifts[3] = { 2.0 * a, 2.0 * a, 2.0 * a };

		int count = 0;

		for (int x = 0; x < dimension; ++x) 
		{
			for (int y = 0; y < dimension; ++y) 
			{
				for (int z = 0; z < dimension; ++z) 
				{
					for (int i = 0; i < 1; ++i) 
					{
						real shiftX = x * cellShifts[0];
						real shiftY = y * cellShifts[1];
						real shiftZ = z * cellShifts[2];
						
						

						// initialize position
						Vec3 position;						
						position.x = cellPositions[i][0] + shiftX;
						position.y = cellPositions[i][1] + shiftY;
						position.z = cellPositions[i][2] + shiftZ;

						// initialize velocity
						Vec3 velocity;
						velocity.x = -6.0 + (rand() * 12.0) / RAND_MAX;
						velocity.y = -6.0 + (rand() * 12.0) / RAND_MAX;
						velocity.z = -6.0 + (rand() * 12.0) / RAND_MAX;

						Particle atom(atom_number, mass, epsilon, sigma, kB, position, velocity);
						
						// set initial temperature
						atom.setTemperature(T0);

						particles_.push_back(atom);

						if (count == Constants::N)
						{
							;
						}

						count++;
					}
				}
			}
		}

		Particle::MovePositionVelocityToCenterOfMass(particles_);

		std::string strings = "";
	}
	Vec3 getAcceleration() const
	{
	return totalAcceleration_;
	}

	real getPotentialEnergyRepulsive() const
	{
	return totalPotentialEnergyRepulsive_;
	}

	real getPotentialEnergyAttractive() const
	{
	return totalPotentialEnergyAttractive_;
	}

	real getPotentialEnergy() const
	{
	return totalPotentialEnergy_;
	}

	real getKineticEnergy() const
	{
	return totalKineticEnergy_;
	}

	real getTotalEnergy() const
	{
	return totalEnergy_;
	}

	real getTemperature() const
	{
	return temperature_;
	}
	*/
};

#endif // !SIM_SYSTEM_HPP