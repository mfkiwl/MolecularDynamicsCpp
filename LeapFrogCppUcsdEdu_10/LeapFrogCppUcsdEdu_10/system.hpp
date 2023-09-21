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
	
	void initialize(real T0)
	{
		particles_.clear();

		// Calculate the variance
		double var = std::sqrt((6 * kB * T0) / mass);
		// Random number generator
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dist(-var, var);

		// initialize grid...
		double a = sigma / std::sqrt(2); // Length unit a

		int particle_no = 0;

		// Create the grid of atoms
		// 6*6*6*4 = 864
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				for (int k = 0; k < dimension; k++)
				{
					// initialize position
					//TODO: initialize position.
					Vec3 position1((i + 0.5) * a, (j + 0.5) * a, (k + 0.5) * a );
					Vec3 position2((i + 0.5) * a, (j + 1.5) * a, (k + 1.5) * a );
					Vec3 position3((i + 1.5) * a, (j + 0.5) * a, (k + 1.5) * a );
					Vec3 position4((i + 1.5) * a, (j + 1.5) * a, (k + 0.5) * a );
					
					//apply periodic bounddary condition
					PBC::Apply(position1);
					PBC::Apply(position2);
					PBC::Apply(position3);
					PBC::Apply(position4);

					// initialize velocity
					Vec3 velocity1(dist(gen), dist(gen), dist(gen));
					Vec3 velocity2(dist(gen), dist(gen), dist(gen));
					Vec3 velocity3(dist(gen), dist(gen), dist(gen));
					Vec3 velocity4(dist(gen), dist(gen), dist(gen));

					Particle atom1(particle_no++, mass, epsilon, sigma, kB, position1, velocity1, neighRadius);
					Particle atom2(particle_no++, mass, epsilon, sigma, kB, position2, velocity2, neighRadius);
					Particle atom3(particle_no++, mass, epsilon, sigma, kB, position3, velocity3, neighRadius);
					Particle atom4(particle_no++, mass, epsilon, sigma, kB, position4, velocity4, neighRadius);

					particles_.push_back(atom1);
					particles_.push_back(atom2);
					particles_.push_back(atom3);
					particles_.push_back(atom4);
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

	real getTemperature()
	{
		int n_particles = particles_.size();
		real dimension = 3.0;
		real v_sq_sum = 0.0;
		for (int i = 0; i < n_particles; i++)
		{
			v_sq_sum += particles_[i].velocity.magnitudeSquared();
		}
		real returns = (mass / (dimension * kB)) * (v_sq_sum/n_particles);
		return returns;
	}
	
	// https://www.ucl.ac.uk/~ucfbasc/Theory/tscale.html
	void setTemperature(real expectedTemperature)
	{
		int n_particles = particles_.size();

		real currentTemperature = getTemperature();

		real scalingFactor = std::sqrt(expectedTemperature / currentTemperature);

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
			//TODO: apply PBC
			PBC::Apply(particle.position);//apply periodic bounddary condition
			particle.velocity -= centerOfMassVelocity;
		}
	}
};

#endif // !SIM_SYSTEM_HPP
