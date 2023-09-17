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
		position = Vec3(0,0,0);
		velocity = Vec3(0, 0, 0);
		temperature=0;
	}

	Particle(int number, real mass, real epsilon, real sigma, real kB, const Vec3& position, const Vec3& velocity)
		: number(number), lj_(epsilon, sigma, kB), mass(mass), position(position), velocity(velocity) {}

	Vec3 getForce()
	{
		return lj_.getForce(position);
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

	real getTemperature()
	{
		return lj_.getTemperature(mass, velocity);
	}

	void setTemperature(real targetTemperature)
	{
		lj_.setTemperature(velocity, temperature, targetTemperature);
	}

	Particle& operator+=(const Particle& other) {
		mass += other.mass;
		position += other.position;
		velocity += other.velocity;
		return *this;
	}

	Particle& operator-=(const Particle& other) {
		mass -= other.mass;
		position -= other.position;
		velocity -= other.velocity;
		return *this;
	}

	Particle operator+(const Particle& other) const {
		Particle result(*this);
		result += other;
		return result;
	}

	Particle operator-(const Particle& other) const {
		Particle result(*this);
		result -= other;
		return result;
	}

	Particle& operator*=(real scalar) {
		mass *= scalar;
		position *= scalar;
		velocity *= scalar;
		return *this;
	}

	Particle operator*(real scalar) const {
		Particle result(*this);
		result *= scalar;
		return result;
	}

	Particle& operator/=(real scalar) {
		mass /= scalar;
		position /= scalar;
		velocity /= scalar;
		return *this;
	}

	Particle operator/(real scalar) const {
		Particle result(*this);
		result /= scalar;
		return result;
	}

	#pragma region  [MovePositionsToCenterOfMass, MoveVelocitiesToCenterOfMass]
	/*
static void MovePositionsToCenterOfMass(std::vector<Particle>& particles)
{
	Vec3 centerOfMass;
	real totalMass = 0.0;

	// Calculate the total mass and the weighted sum of positions
	for (const auto& particle : particles)
	{
		centerOfMass += particle.position * particle.mass;
		totalMass += particle.mass;
	}

	// Calculate the center of mass
	centerOfMass /= totalMass;

	// Move the positions relative to the center of mass
	for (auto& particle : particles)
	{
		particle.position -= centerOfMass;
	}
}

static void MoveVelocitiesToCenterOfMass(std::vector<Particle>& particles)
{
	Vec3 centerOfMassVelocity;
	real totalMass = 0.0;

	// Calculate the total mass and the weighted sum of velocities
	for (const auto& particle : particles)
	{
		centerOfMassVelocity += particle.velocity * particle.mass;
		totalMass += particle.mass;
	}

	// Calculate the center of mass velocity
	centerOfMassVelocity /= totalMass;

	// Move the velocities relative to the center of mass velocity
	for (auto& particle : particles)
	{
		particle.velocity -= centerOfMassVelocity;
	}
}*/
#pragma endregion

	static void MovePositionVelocityToCenterOfMass(std::vector<Particle>& particles_)
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
#endif // !PARTICLE_HPP
