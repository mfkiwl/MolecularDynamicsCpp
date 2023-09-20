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
	std::vector<Particle> particles_;

public:
	int getParticlesCount()
	{
		return particles_.size();
	}

public:
	real dimension;
	real sigma;
	real epsilon;
	real mass;
	real kB;
	real rCutOff;
	real neighRadius;

	System()
	{
		dimension = 0;
		sigma = 0;
		epsilon = 0;
		mass = 0;
		kB = 0;
		rCutOff = 0;
		neighRadius = 0;
	}

	System(real sigma, real epsilon, real mass, real kB, real dimension, real rCutOff, real neighRadius):
		sigma(sigma), epsilon(epsilon), mass(mass), kB(kB), dimension(dimension), rCutOff(rCutOff), neighRadius(neighRadius)
	{
	}

	
	void initialize(int n_particles, real T0)
	{
		// Calculate the variance
		double var = std::sqrt((6 * kB * T0) / mass);
		// Random number generator
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dist(-var, var);

		// initialize grid...
		double a = 0.5 * std::sqrt(2); // Length unit a

		// Coordinates of atoms in the elementary cell
		Vec3 atom1 = { 0.5 * a, 0.5 * a, 0.5 * a };
		Vec3 atom2 = { 0.5 * a, 1.5 * a, 1.5 * a };
		Vec3 atom3 = { 1.5 * a, 0.5 * a, 1.5 * a };
		Vec3 atom4 = { 1.5 * a, 1.5 * a, 0.5 * a };

		int particleCount_ = 0;

		// Create the grid of atoms
		// 6*6*6*4 = 864
		for (int x = 0; x < dimension; x++) 
		{
			for (int y = 0; y < dimension; y++)
			{
				for (int z = 0; z < dimension; z++)
				{
					for (size_t i = 0; i < 4; i++)
					{
						// initialize position
						Vec3 position;

						//TODO: initialize position.

						PBC::Apply(position);//apply periodic bounddary condition

						// initialize velocity
						Vec3 velocity;
						velocity.x = dist(gen);
						velocity.y = dist(gen);
						velocity.z = dist(gen);

						Particle atom(particleCount_, mass, epsilon, sigma, kB, position, velocity, neighRadius);

						particles_.push_back(atom);

						particleCount_++;
					}										
				}
			}
		}

		MoveToCenterOfMass();
	}

	EnergyData computeEnergy(int step_no)
	{
		Vec3 totalAcceleration_(0, 0, 0);
		real totalPotentialEnergyRepulsive_ = 0;
		real totalPotentialEnergyAttractive_ = 0;
		real totalPotentialEnergy_ = 0;
		real totalKineticEnergy_ = 0;
		real totalEnergy_ = 0;
		real currentTemperature_ = 0;

		int n_particles = particles_.size();

		for (size_t i = 0; i < n_particles; i++)
		{
			const Particle& particle = particles_[i];
			const std::vector<Particle> neighborList = particle.getNeighborList();

			for (size_t j = i + 1; j < n_particles; j++)
			{
				const Particle& other = neighborList[j];

				if (particle.isWithinCutOff(other, rCutOff))
				{
					double kineticEnergy = particle.getKineticEnergy();
					double potEngyAttrac = particle.getPotentialEnergyAttractive(other);
					double potEngyRepuls = particle.getPotentialEnergyRepulsive(other);
					double potentlEnergy = particle.getPotentialEnergy(other);
					double totalEnergy = particle.getTotalEnergy(other);

					totalKineticEnergy_ += kineticEnergy;
					totalPotentialEnergyAttractive_ += potEngyAttrac;
					totalPotentialEnergyRepulsive_ += potEngyRepuls;
					totalPotentialEnergy_ += potentlEnergy;
					totalEnergy_ += totalEnergy;
				}
			}
		}

		EnergyData data;
		data.step_no = step_no;
		data.KineticEngy = totalKineticEnergy_ * 0.5;
		data.PotEngyAttractive = totalPotentialEnergyAttractive_ * 0.5;
		data.PotEngyRepulsive = totalPotentialEnergyRepulsive_ * 0.5;
		data.PotenEnergy = totalPotentialEnergy_ * 0.5;
		data.PotEngyBalloon = 0 * 0.5;

		return data;
	}

	void buildNeighborList()
	{
		int n_particles = particles_.size();
		for (size_t i = 0; i < n_particles; i++)
		{
			particles_[i].buildNeighborList(particles_);
		}
	}

	double getTemperature()
	{
		int n_particles = particles_.size();
		real currentTemperature = 0.0;
		for (int i = 0; i < n_particles; i++)
		{
			real lenSq = particles_[i].velocity.magnitudeSquared();

			currentTemperature += 0.5 * mass * lenSq / n_particles;
		}
		return currentTemperature;
	}

	void scaleTemperature(real targetTemperature)
	{
		int n_particles = particles_.size();

		real currentTemperature = getTemperature();

		real scalingFactor = std::sqrt(targetTemperature / currentTemperature);

		for (int i = 0; i < n_particles; i++)
		{
			particles_[i].velocity *= scalingFactor;
		}
	}

	std::vector<Particle>& getParticles()
	{
		return particles_;
	}

private:
	void MoveToCenterOfMass()
	{
		Vec3 centerOfMassVelocity;
		Vec3 centerOfMass;
		real totalMass = 0.0;

		// Calculate the total mass and the weighted sum of positions
		for (const auto& particle : particles_)
		{
			centerOfMass += particle.position * particle.mass;
			centerOfMassVelocity += particle.velocity * particle.mass;
			totalMass += particle.mass;
		}

		// Calculate the center of mass
		centerOfMass /= totalMass;
		centerOfMassVelocity /= totalMass;

		// Move the positions relative to the center of mass
		for (auto& particle : particles_)
		{
			particle.position -= centerOfMass;
			particle.velocity -= centerOfMassVelocity;
		}
	}
};

#endif // !SIM_SYSTEM_HPP
