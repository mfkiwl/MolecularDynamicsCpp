#pragma once

#include "common.hpp"
#include "vec3.hpp"

class Baloon
{
public:
	static real BalloonConstant;
	static real baloonRadius;
public:
	static void ApplyPotential(Vec3& potential)
	{		
		if (potential.magnitude() > baloonRadius)
		{
			Vec3 ri_rB( potential.x - baloonRadius, 
						potential.y - baloonRadius, 
						potential.z - baloonRadius);
			
			potential = 0.5 * BalloonConstant * (ri_rB * ri_rB);
		}
		else
		{
			potential = Vec3(0, 0, 0);
		}
	}

	static void ApplyForce(Vec3& force)
	{
		if (force.magnitude() > baloonRadius)
		{
			Vec3 ri_rB(	force.x - baloonRadius,
						force.y - baloonRadius,
						force.z - baloonRadius);

			force = (-1.0) * BalloonConstant * ri_rB * (force.magnitude() / force);
		}
		else
		{
			force = Vec3(0, 0, 0);
		}
	}
};

