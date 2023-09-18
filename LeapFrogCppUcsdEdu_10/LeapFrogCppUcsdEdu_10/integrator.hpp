#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include "Particle.hpp"

class Integrator
{
public:
	static void Lepfrog(std::vector<Particle>& particles_, double dt)
	{
		int n_particles = particles_.size();

		// Compute acceleration and half velocity step for all particles
		for (int i = 0; i < n_particles; i++)
		{
			Particle& particle = particles_[i];
			
			Vec3 acceleration;
			for (int j = 0; j < n_particles; j++)
			{
				if (i != j)
				{
					Particle& other = particles_[j];
					acceleration += particle.getAcceleration(other);
				}
			}
			particle.velocity += 0.5 * dt * acceleration; // half velocity step
		}

		// Update position and full velocity step for all particles
		for (int i = 0; i < n_particles; i++)
		{
			Particle& particle = particles_[i];
			particle.position += dt * particle.velocity; // full position step

			Vec3 acceleration;
			for (int j = 0; j < n_particles; j++)
			{
				if (i != j)
				{
					Particle& other = particles_[j];
					acceleration += particle.getAcceleration(other);
				}
			}
			particle.velocity += 0.5 * dt * acceleration; // complete velocity step
		}
	}
};

#endif // !INTEGRATOR_HPP