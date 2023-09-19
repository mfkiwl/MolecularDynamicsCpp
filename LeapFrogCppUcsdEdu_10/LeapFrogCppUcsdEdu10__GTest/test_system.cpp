#include "pch.h"
#include "header.h"

TEST(TestSystem, TestCenterOfMass)
{
	real rCutOff = 0.9;

	Vec3 position1(0.25, 0.25, 0.25);
	Vec3 position2(0.5, 0.5, 0.5);
	Vec3 position3(0.75, 0.75, 0.75);
	Vec3 position4(0.5, 0.5, 0.5);

	Vec3 velocity1(0.25, 0.25, 0.25);
	Vec3 velocity2(0.5, 0.5, 0.5);
	Vec3 velocity3(0.75, 0.75, 0.75);
	Vec3 velocity4(0.5, 0.5, 0.5);

	Particle particle1(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position1, velocity1);

	Particle particle2(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position2, velocity2);

	Particle particle3(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position3, velocity3);

	Particle particle4(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position4, velocity4);

	bool isWithinCut2 = particle3.isWithinCutOff(particle4, rCutOff);

	EXPECT_EQ(false, isWithinCut1);
	EXPECT_EQ(true, isWithinCut2);
}