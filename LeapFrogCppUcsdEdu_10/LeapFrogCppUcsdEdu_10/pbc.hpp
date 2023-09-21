#pragma once

#include "common.hpp"
#include "vec3.hpp"

class PBC
{
public:
	static real boxLength;

	// Applies the periodic boundary condition to a single value
	static void Apply(real& value) {
		if (value < 0) {
			value += boxLength;
		}
		else if (value >= boxLength) {
			value -= boxLength;
		}
	}

	static void Apply(Vec3& vec)
	{
		Apply(vec.x);
		Apply(vec.y);
		Apply(vec.z);
	}
};

