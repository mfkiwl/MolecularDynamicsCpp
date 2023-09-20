#include "pch.h"
#include "header.h"

TEST(TestParticle, TestIsWithinCutOff)
{
	real rCutOff = 0.9;
	real neighborRadius = 90;

	Vec3 position1(0, 0, 0);
	Vec3 position2(1, 1, 1);

	Vec3 velocity1(0, 0, 0);
	Vec3 velocity2(1, 1, 1);

	Particle particle1(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position1, velocity1, neighborRadius);

	Particle particle2(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position2, velocity2, neighborRadius);

	bool isWithinCut1 = particle1.isWithinCutOff(particle2, rCutOff);

	//============================================//
	Vec3 position3(0, 0, 0);
	Vec3 position4(0.5, 0.5, 0.5);

	Vec3 velocity3(0, 0, 0);
	Vec3 velocity4(0.5, 0.5, 0.5);

	Particle particle3(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position3, velocity3, neighborRadius);

	Particle particle4(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position4, velocity4, neighborRadius);

	bool isWithinCut2 = particle3.isWithinCutOff(particle4, rCutOff);

	EXPECT_EQ(false, isWithinCut1);
	EXPECT_EQ(true, isWithinCut2);
}

TEST(TestParticle, TestParticlePotentialEnergyAttractiveRepulsive)
{
	real rCutOff = 0.9;
	real neighborRadius = 90;

	Vec3 position1(0, 0, 0);
	Vec3 position2(1, 1, 1);

	Vec3 velocity1(0, 0, 0);
	Vec3 velocity2(1, 1, 1);

	Particle particle1(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position1, velocity1, neighborRadius);

	Particle particle2(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position2, velocity2, neighborRadius);

	real attractive = particle1.getPotentialEnergyAttractive(particle2);
	real repulsive = particle1.getPotentialEnergyRepulsive(particle2);
	real sums = attractive + repulsive;
	real potential = particle1.getPotentialEnergy(particle2);

	EXPECT_NEAR(potential, sums, 0.00001);
}


TEST(TestParticle, TestParticleKineticEnergy)
{
	real rCutOff = 0.9;
	real neighborRadius = 90;

	Particle particle(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, Vec3(1, 1, 1), Vec3(1, 1, 1), neighborRadius);

	real kinetic = particle.getKineticEnergy();

	EXPECT_NEAR(29.9625, kinetic, 0.01);
}

TEST(TestParticle, TestParticlePotentialEnergy)
{	
	real rCutOff = 0.9;
	real neighborRadius = 90;

	Vec3 position1(0, 0, 0);
	Vec3 position2(1, 1, 1);

	Vec3 velocity1(0, 0, 0);
	Vec3 velocity2(1, 1, 1);
	
	Particle particle1(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position1, velocity1, neighborRadius);

	Particle particle2(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, position2, velocity2, neighborRadius);

	real force = particle1.getPotentialEnergy(particle2);

	EXPECT_NEAR(-0.00011127498, force, 0.00001);
}

TEST(TestParticle, TestParticleForce)
{
	real rCutOff = 0.9;
	real neighborRadius = 90;

	Particle particle(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, Vec3(1, 1, 1),
		Vec3(1, 1, 1), neighborRadius);
	Particle other(1, Constants::ATOMIC_MASS,
		Constants::EPSILON, Constants::SIGMA,
		Constants::KB, Vec3(0, 0, 0),
		Vec3(1, 1, 1), neighborRadius);

	Vec3 force = particle.getForce(other);

	EXPECT_NEAR(-0.00044463402, force.x, 0.00001);
	EXPECT_NEAR(-0.00044463402, force.y, 0.00001);
	EXPECT_NEAR(-0.00044463402, force.z, 0.00001);
}