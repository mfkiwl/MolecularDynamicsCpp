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

	EnergyData computeEnergy(int step_no)
	{
		int n_particles = particles_.size();

		for (size_t i = 0; i < n_particles; i++)
		{
			Vec3 particleAcceleration(0.0, 0.0, 0.0);

			const Particle& particle = particles_[i];

			for (size_t j = i + 1; j < n_particles; j++)
			{
				const Particle& other = particles_[j];			

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


	void initialize(real T0)
	{
		// Calculate the number of particles in each dimension of the cell
		int particlesPerDimension = std::cbrt(Constants::N);

		// Calculate the spacing between particles in each dimension
		double spacing = Constants::BOX_SIZE / particlesPerDimension;

		// Generate random positions and velocities for the particles
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> posDist(0.0, spacing);
		std::uniform_real_distribution<double> velDist(-Constants::MAX_VELOCITY, Constants::MAX_VELOCITY);

		for (int i = 0; i < particlesPerDimension; i++)
		{
			for (int j = 0; j < particlesPerDimension; j++)
			{
				for (int k = 0; k < particlesPerDimension; k++)
				{
					// Calculate the position of the particle within the cell
					double x = i * spacing + posDist(gen);
					double y = j * spacing + posDist(gen);
					double z = k * spacing + posDist(gen);

					// Generate a random velocity for the particle
					double vx = velDist(gen);
					double vy = velDist(gen);
					double vz = velDist(gen);

					// Create the particle and add it to the system
					Particle particle(i * particlesPerDimension * particlesPerDimension + j * particlesPerDimension + k,
						Constants::ATOMIC_MASS, Constants::EPSILON, Constants::SIGMA, Constants::KB,
						Vec3(x, y, z), Vec3(vx, vy, vz));

					particles_.push_back(particle);
				}
			}
		}

		Particle::MovePositionVelocityToCenterOfMass(particles_);

		std::string st = "";
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
