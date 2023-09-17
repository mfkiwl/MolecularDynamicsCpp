﻿#ifndef SYSTEM_HPP
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
	real temperature_;

public:
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
		return totalPotentialEnergy_;
	}

	real getTotalEnergy() const
	{
		return totalEnergy_;
	}

	real getTemperature() const
	{
		return temperature_;
	}

private:
	int count_;
	std::vector<Particle> particles_;

public:
	int getParticlesCount()
	{
		return count_;
	}

public:
	real dimension;
	real sigma;
	real epsilon;
	real mass;
	real kB;

	System()
	{
		totalAcceleration_.x = 0; totalAcceleration_.y = 0; totalAcceleration_.z = 0;
		totalPotentialEnergyRepulsive_ = 0.0;
		totalPotentialEnergyAttractive_ = 0.0;
		totalPotentialEnergy_ = 0.0;
		totalKineticEnergy_ = 0.0;
		totalEnergy_ = 0.0;
		temperature_ = 0.0;

		count_ = 0;

		dimension = 0;
		sigma = 0;
		epsilon = 0;
		mass = 0;
		kB = 0;
	}

	System(real sigma, real epsilon, real mass, real kB, real dimension): 
		sigma(sigma), epsilon(epsilon), mass(mass), kB(kB), dimension(dimension)
	{
		totalAcceleration_.x = 0; totalAcceleration_.y = 0; totalAcceleration_.z = 0;
		totalPotentialEnergyRepulsive_ = 0.0;
		totalPotentialEnergyAttractive_ = 0.0;
		totalPotentialEnergy_ = 0.0;
		totalKineticEnergy_ = 0.0;
		totalEnergy_ = 0.0;
		temperature_ = 0.0;

		count_ = 0;
	}

	void computeEnergy()
	{
		int n_particles = particles_.size();

		for (size_t i = 0; i < n_particles ; i++)
		{
			Vec3 particleAcceleration(0.0, 0.0, 0.0);

			const Particle& particle = particles_[i];

			for (size_t j = i + 1; j < n_particles ; j++)
			{
				const Particle& other = particles_[j];

				particleAcceleration += particle.getAcceleration(other);
				totalPotentialEnergyRepulsive_ += particle.getPotentialEnergyRepulsive(other);
				totalPotentialEnergyAttractive_ += particle.getPotentialEnergyAttractive(other);
				totalPotentialEnergy_ = particle.getPotentialEnergy(other);
			}

			totalKineticEnergy_ += particle.getKineticEnergy();
		}

		totalEnergy_ = totalPotentialEnergy_ + totalKineticEnergy_;
		temperature_ = (2.0 * totalKineticEnergy_) / (3.0 * kB * n_particles);
	}

	void setTemperature(real deltaTemperature)
	{
		real currentTemperature = getTemperature();
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
					for (int i = 0; i < 4; ++i) 
					{
						real shiftX = x * cellShifts[0];
						real shiftY = y * cellShifts[1];
						real shiftZ = z * cellShifts[2];

						
						int atom_number = count + 1;

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

						count++;
					}
				}
			}
		}

		Particle::MovePositionVelocityToCenterOfMass(particles_);
	}
};

#endif // !SIM_SYSTEM_HPP