#pragma once

#include "common.hpp"
#include "vec3.hpp"

/*
double PeriodicBoundaryCondition(double value)
{
	if (value > 17)
		value -= 34;
	if (value < -17)
		value += 34;

	return value;
}
*/

class PBC //Periodic Boundary Condition
{
public:
	 static real boxLength;

	static void Apply(real & value) 
	{
		real boxLengthHalf = boxLength / 2.0;

		if (value > boxLengthHalf)
			value -= boxLength;
		if (value < -boxLengthHalf)
			value += boxLength;
	}

	static void Apply(Vec3 & vec)
	{
		Apply(vec.x);
		Apply(vec.y);
		Apply(vec.z);
	}
};

