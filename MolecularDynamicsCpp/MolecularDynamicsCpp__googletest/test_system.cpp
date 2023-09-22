#include "pch.h"
#include "header.h"

TEST(TestSystem, TestInitialization)
{
	System system;
	system.dimension = 1;
	system.epsilon = Constants::EPSILON;
	system.kB = Constants::KB;
	system.mass = Constants::ATOMIC_MASS;
	system.neighRadius = Constants::NEIGHBOR_RADIUS;
	system.rCutOff = Constants::R_CUTOFF;
	system.sigma = Constants::SIGMA;

	system.initialize(Constants::INIT_TEMPTR);
	size_t count1 = 4;
	EXPECT_EQ(count1, system.getParticlesCount());

	system.dimension = 2;
	system.initialize(Constants::INIT_TEMPTR);
	size_t count2 = 32;
	EXPECT_EQ(count2, system.getParticlesCount());
}

TEST(TestSystem, TestTemperature)
{
	System system;
	system.dimension = 1;
	system.epsilon = Constants::EPSILON;
	system.kB = Constants::KB;
	system.mass = Constants::ATOMIC_MASS;
	system.neighRadius = Constants::NEIGHBOR_RADIUS;
	system.rCutOff = Constants::R_CUTOFF;
	system.sigma = Constants::SIGMA;

	system.initialize(Constants::INIT_TEMPTR);

	real T0 = 300;

	system.setTemperature(T0);

	real temp = system.getTemperature();

	EXPECT_NEAR(T0, temp, 0.00001);
}

TEST(TestSystem, TestCenterOfMass)
{
	real rCutOff = 0.9;
	real neighborRadius = 90;

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
		Constants::KB, position1, velocity1, neighborRadius);

	Particle particle2(2, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position2, velocity2, neighborRadius);

	bool isWithinCut1 = particle1.isWithinCutOff(particle2, rCutOff);

	Particle particle3(3, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position3, velocity3, neighborRadius);

	Particle particle4(4, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position4, velocity4, neighborRadius);

	bool isWithinCut2 = particle3.isWithinCutOff(particle4, rCutOff);

	//EXPECT_EQ(false, isWithinCut1);
	//EXPECT_EQ(true, isWithinCut2);
}