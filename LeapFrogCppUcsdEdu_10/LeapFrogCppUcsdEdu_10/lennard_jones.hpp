#ifndef LJ_HPP
#define LJ_HPP

#include <vector>

#include "common.hpp"
#include "vec3.hpp"

class LennardJones
{
public:
	real kB;
	real epsilon;
	real sigma;

public:
	LennardJones()
	{
		kB = 0;
		epsilon = 0;
		sigma = 0;
	}

	LennardJones(double epsilon, double sigma, real kB) : epsilon(epsilon), sigma(sigma), kB(kB) {}

	real getPotential(const Vec3& distance) const
	{
		real r_mag = std::sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
		real s_over_r = sigma / r_mag;
		real s_over_r6 = pow(s_over_r, 6);
		return epsilon * (s_over_r6 * s_over_r6 - 2.0 * s_over_r6);
	}

	real getPotentialAttractive(const Vec3& distance) const
	{
		real r_mag = std::sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
		real s_over_r = sigma / r_mag;
		real s_over_r6 = pow(s_over_r, 6);
		real attrPotential = (-2.0) * epsilon * s_over_r6;
		return attrPotential;
	}

	real getPotentialRepulsive(const Vec3& distance) const
	{
		real r_mag = std::sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);
		real s_over_r = sigma / r_mag;
		real s_over_r12 = pow(s_over_r, 12);
		real repPotential = epsilon * s_over_r12;
		return repPotential;
	}

	Vec3 getForceApprox(const Vec3& distance) const
	{
		// Define a small distance for the derivative approximation
		real dr = 1e-6;
		Vec3 force;
		std::vector<Vec3> r_plus_dr = { distance, distance, distance };
		r_plus_dr[0].x += dr;
		r_plus_dr[1].y += dr;
		r_plus_dr[2].z += dr;

		// The force is the negative derivative of the potential energy
		force.x = -(getPotential(r_plus_dr[0]) - getPotential(distance)) / dr;
		force.y = -(getPotential(r_plus_dr[1]) - getPotential(distance)) / dr;
		force.z = -(getPotential(r_plus_dr[2]) - getPotential(distance)) / dr;
		return force;
	}

	Vec3 getAcceleration(const Vec3& distance, double mass) const
	{
		double rSquared = distance.x * distance.x + distance.y * distance.y + distance.z * distance.z;
		double r6 = std::pow(sigma * sigma / rSquared, 3);
		double r12 = r6 * r6;

		double magnitude = 24.0 * epsilon / mass * (2.0 * r12 - r6) / rSquared;

		Vec3 acceleration(distance.x * magnitude, distance.y * magnitude, distance.z * magnitude);
		return acceleration;
	}

	Vec3 getForce(Vec3 position) const
	{
		real r_mag = std::sqrt(position.x * position.x + position.y * position.y + position.z * position.z);
		real s_over_r = sigma / r_mag;
		real s_over_r6 = s_over_r * s_over_r * s_over_r * s_over_r * s_over_r * s_over_r;
		real s_over_r12 = s_over_r6 * s_over_r6;
		real factor = 24.0 * epsilon * (2.0 * s_over_r12 - s_over_r6) / (r_mag * r_mag * r_mag);

		Vec3 force;
		force.x = factor * position.x;
		force.y = factor * position.y;
		force.z = factor * position.z;
		return force;
	}

	real getKineticEnergy(real mass, const Vec3& velocity) const
	{
		real vx = velocity.x;
		real vy = velocity.y;
		real vz = velocity.z;
		return 0.5 * mass * (vx * vx + vy * vy + vz * vz);
	}

	real getTotalEnergy(real mass, const Vec3& distance, const Vec3& velocity) const
	{
		real potentialEnergy = getPotential(distance);
		real kineticEnergy = getKineticEnergy(mass, velocity);
		return potentialEnergy + kineticEnergy;
	}

	/*double getTemperature(real mass, const Vec3& velocity) const
	{		
		double kineticEnergy = getKineticEnergy(mass, velocity);
		double temperature = (2.0 * kineticEnergy) / (3.0 * kB);
		return temperature;
	}

	void setTemperature(Vec3& velocity, real currentTemperature, real targetTemperature) const
	{
		real scalingFactor = std::sqrt(targetTemperature / currentTemperature);
		velocity *= scalingFactor;
	}*/

	double getTemperature(double mass, const Vec3& velocity) const
	{
		double kineticEnergy = getKineticEnergy(mass, velocity);
		double degreesOfFreedom = 3; // Assuming 3 degrees of freedom for simplicity
		double kB_Nf = kB * degreesOfFreedom;
		double temperature = (2.0 / (kB_Nf * mass)) * kineticEnergy;
		return temperature;
	}

	void setTemperature(double targetTemperature, double mass, Vec3& velocity) const
	{
		double currentTemperature = getTemperature(mass, velocity);
		double scalingFactor = std::sqrt(targetTemperature / currentTemperature);
		velocity *= scalingFactor;
	}

	
};
#endif // !LJ_HPP


