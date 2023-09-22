#pragma once

#include "common.hpp"
#include "vec3.hpp"

class Baloon
{
public:
	static real BalloonConstant;
	static real baloonRadius;
public:
	static void ApplyPotential(Vec3& position)
	{		
		if (position.magnitude() > baloonRadius)
		{
			Vec3 ri_rB( position.x - baloonRadius, 
						position.y - baloonRadius, 
						position.z - baloonRadius);
			
			position = 0.5 * BalloonConstant * (ri_rB * ri_rB);
		}
		else
		{
			position = Vec3(0, 0, 0);
		}
	}

	static void ApplyForce(Vec3& force, Vec3& position)
	{
		if (force.magnitude() > baloonRadius)
		{
			Vec3 ri_rB(	position.x - baloonRadius,
						position.y - baloonRadius,
						position.z - baloonRadius);

			real pos_mag = position.magnitude();

			force.x = ((force.x / pos_mag) * (-1.0) * BalloonConstant * ri_rB).x;
			force.y = ((force.y / pos_mag)  * (-1.0) * BalloonConstant * ri_rB).y;
			force.z = ((force.z / pos_mag) * (-1.0) * BalloonConstant * ri_rB).z;
		}
		else
		{
			force = Vec3(0, 0, 0);
		}
	}
};

