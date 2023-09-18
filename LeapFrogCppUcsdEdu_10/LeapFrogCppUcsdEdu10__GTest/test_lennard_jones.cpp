#include "pch.h"
#include "header.h"


Particle particle(1, Constants::ATOMIC_MASS,
	Constants::EPSILON, Constants::SIGMA,
	Constants::KB, Vec3(1, 1, 1),
	Vec3(1, 1, 1));
Particle other(1, Constants::ATOMIC_MASS,
	Constants::EPSILON, Constants::SIGMA,
	Constants::KB, Vec3(0, 0, 0),
	Vec3(1, 1, 1));

TEST(TestCaseName2, TestParticleAccel)
{
	Vec3 accel = particle.getAcceleration(other);

	char ch = '\n';
}

LennardJones lj(Constants::EPSILON, Constants::SIGMA, Constants::KB);

TEST(TestCaseName, TestLennardJonesFormula) 
{
	Vec3 diatance(4.0, 4.0, 4.0);	

	real attractive = lj.getPotentialAttractive(diatance);
	real repulsive = lj.getPotentialRepulsive(diatance);
	real total = lj.getPotential(diatance);
	
	//-2.42146e-06
	// 1.70618e-08

	EXPECT_NEAR(-2.42146e-06, attractive, Constants::TOLERANCE);
	EXPECT_NEAR(1.70618e-06, repulsive, Constants::TOLERANCE);
	EXPECT_NEAR(total, attractive + repulsive, Constants::TOLERANCE);
}

TEST(TestCaseName, TestLennardJonesAcceleration)
{
	Vec3 diatance(4.0, 4.0, 4.0);

	Vec3 acceleration = lj.getAcceleration(diatance, Constants::ATOMIC_MASS);

	//x=-5.8906850635166447e-08 
	//y=-5.8906850635166447e-08 
	//z=-5.8906850635166447e-08

	EXPECT_NEAR(-5.89068e-08, acceleration.x, Constants::TOLERANCE);
	EXPECT_NEAR(-5.89068e-08, acceleration.y, Constants::TOLERANCE);
	EXPECT_NEAR(-5.89068e-08, acceleration.z, Constants::TOLERANCE);
}

