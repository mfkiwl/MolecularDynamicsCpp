#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "common.hpp"
#include "vec3.hpp"
#include "lennard_jones.hpp"

class Particle
{
private:
	LennardJones lj_;

public:
	int number;
	real mass;
	Vec3 position;
	Vec3 velocity;
	real temperature;

	Particle()
	{
		number = 0;
		mass = 0;
		position = Vec3(0, 0, 0);
		velocity = Vec3(0, 0, 0);
		temperature = 0;
	}

	Particle(int number, real mass, real epsilon, real sigma, real kB, const Vec3& position, const Vec3& velocity)
		: number(number), lj_(epsilon, sigma, kB), mass(mass), position(position), velocity(velocity) {}

	Particle(const Particle& other)
		: lj_(other.lj_), number(other.number), mass(other.mass), position(other.position), velocity(other.velocity), temperature(other.temperature) {}

	Particle& operator=(const Particle& other)
	{
		if (this != &other)
		{
			lj_ = other.lj_;
			number = other.number;
			mass = other.mass;
			position = other.position;
			velocity = other.velocity;
			temperature = other.temperature;
		}
		return *this;
	}

	Vec3 getForce(const Particle& other)
	{
		Vec3 distance = position - other.position;
		return lj_.getForce(distance);
	}

	real getKineticEnergy() const
	{
		return lj_.getKineticEnergy(mass, velocity);
	}

	Vec3 getAcceleration(const Particle& other) const
	{
		Vec3 distance = position - other.position;
		return lj_.getAcceleration(distance, mass);
	}

	real getPotentialEnergyRepulsive(const Particle& other) const
	{
		Vec3 distance = position - other.position;
		return lj_.getPotentialRepulsive(distance);
	}

	real getPotentialEnergyAttractive(const Particle& other) const
	{
		Vec3 distance = position - other.position;
		return lj_.getPotentialAttractive(distance);
	}

	real getPotentialEnergy(const Particle& other) const
	{
		Vec3 distance = position - other.position;
		return lj_.getPotential(distance);
	}

	real getTotalEnergy(const Particle& other) const
	{
		real potentialEnergy = getPotentialEnergy(other);
		real kineticEnergy = getKineticEnergy();
		return potentialEnergy + kineticEnergy;
	}

	bool isWithinCutOff(const Particle& other, real rCutOff) const
	{
		Particle temp = *this;
		Vec3 distance = temp.position - other.position;
		double r = distance.magnitude();
		return r <= rCutOff;
	}
};

#endif // !PARTICLE_HPP