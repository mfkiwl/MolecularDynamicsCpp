#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include "particle.hpp"


class Integrator
{
private:
	// https://github.com/fionn/orbit/blob/master/orbit.cpp
	static void update_position(std::vector<Particle>& particles_, double dt)
	{
		int n_particles = particles_.size();
		for (int i = 0; i < n_particles; i++)      
			particles_[i].position += dt * particles_[i].velocity;
	}

	static void update_velocity(std::vector<Particle>& particles_, double dt)
	{
		int n_particles = particles_.size();

		for (int i = 0; i < n_particles; i++)
		{
			for (int j = 0; j < n_particles; j++)
			{
				if (j != i)
				{
					Vec3 r_ij; 
					Vec3 r_ij2;

					r_ij = particles_[i].position - particles_[j].position;
					r_ij2 += r_ij * r_ij;

					Vec3 r_ij3 = r_ij2.pow(1.5);

					particles_[i].velocity -= dt * particles_[j].mass * r_ij / r_ij3;
				}
			}
		}
	}

public:
	static void Lepfrog(std::vector<Particle>& particles_, double dt)
	{
		update_position(particles_, 0.5 * dt);
		update_velocity(particles_, dt);
		update_position(particles_, 0.5 * dt);
	}

	// http://www.artcompsci.org/vol_1/v1_web/node34.html
	//static void Lepfrog(std::vector<Particle>& particles_, double dt)
	//{
	//	int n_particles = particles_.size();
	//
	//	// Compute acceleration and half velocity step for all particles
	//	for (int i = 0; i < n_particles; i++)
	//	{
	//		Particle& particle = particles_[i];
	//		
	//		Vec3 acceleration;
	//		for (int j = 0; j < n_particles; j++)
	//		{
	//			if (i != j)
	//			{
	//				Particle& other = particles_[j];
	//				acceleration += particle.getAcceleration(other);
	//				particle.velocity += 0.5 * dt * acceleration; // update velocity by half step
	//			}
	//		}			
	//	}
	//
	//	// Update position and another half velocity step for all particles
	//	for (int i = 0; i < n_particles; i++)
	//	{
	//		Particle& particle = particles_[i];
	//		particle.position += dt * particle.velocity; // update position by full step
	//
	//		PBC::Apply(particle.position); //apply periodic boundary condition
	//
	//		Vec3 acceleration;
	//		for (int j = 0; j < n_particles; j++)
	//		{
	//			if (i != j)
	//			{
	//				Particle& other = particles_[j];
	//				acceleration = particle.getAcceleration(other);
	//				particle.velocity += 0.5 * dt * acceleration; // update velocity by half step
	//			}
	//		}			
	//	}
	//}
};

#endif // !INTEGRATOR_HPP