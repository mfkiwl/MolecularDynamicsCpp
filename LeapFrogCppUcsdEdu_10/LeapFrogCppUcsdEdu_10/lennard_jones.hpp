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
		real r_mag = distance.magnitude();
		real s_over_r = sigma / r_mag;
		real s_over_r6 = pow(s_over_r, 6);
		real s_over_r12 = s_over_r6 * s_over_r6;
		real ep05 = 0.5 * epsilon;
		real r12_6 = s_over_r12 - (2.0 * s_over_r6);
		real returns = ep05 * r12_6;
		return returns;
	}

	real getPotentialAttractive(const Vec3& distance) const
	{
		real r_mag = distance.magnitude();
		real s_over_r = sigma / r_mag;
		real s_over_r6 = pow(s_over_r, 6);
		real attrPotential = 0.5* (-2.0) * epsilon * s_over_r6;
		return attrPotential;
	}

	real getPotentialRepulsive(const Vec3& distance) const
	{
		real r_mag = distance.magnitude();
		real s_over_r = sigma / r_mag;
		real s_over_r12 = pow(s_over_r, 12);
		real repPotential = 0.5*epsilon * s_over_r12;
		return repPotential;
	}

	Vec3 getForce(Vec3 distance) const
	{
		real r_mag = distance.magnitude();
		real s_over_r = sigma / r_mag;
		real s_over_r6 = pow(s_over_r, 6);
		real s_over_r12 = s_over_r6 * s_over_r6;
		
		real fx = (12.0 * epsilon * (s_over_r12 - s_over_r6)) * ((distance.x) / (r_mag * r_mag));
		real fy = (12.0 * epsilon * (s_over_r12 - s_over_r6)) * ((distance.y) / (r_mag * r_mag));
		real fz = (12.0 * epsilon * (s_over_r12 - s_over_r6)) * ((distance.z) / (r_mag * r_mag));

		return Vec3(fx, fy, fz);
	}

	Vec3 getAcceleration(const Vec3& distance, double mass) const
	{
		Vec3 force = getForce(distance);
		return force / mass;
	}

	real getKineticEnergy(real mass, const Vec3& velocity) const
	{
		real v_squared = velocity.magnitudeSquared();
		real returns = 0.5 * 0.5 * mass * v_squared;
		return returns;
	}

	real getTotalEnergy(real mass, const Vec3& distance, const Vec3& velocity) const
	{
		real potentialEnergy = getPotential(distance);
		real kineticEnergy = getKineticEnergy(mass, velocity);
		return potentialEnergy + kineticEnergy;
	}
};
#endif // !LJ_HPP


