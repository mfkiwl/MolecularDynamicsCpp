#include "pch.h"
#include "header.h"
#include "../LeapFrogCppUcsdEdu_10/pbc.hpp"
#include "../LeapFrogCppUcsdEdu_10/pbc_static.hpp"

TEST(TestPBC, TestApply)
{
	real rCutOff = 0.9;
	real neighborRadius = 90;

	Vec3 position1(-90, 90, 45);
	Vec3 position2(90, -45, 45);

	PBC::Apply(position1);
	PBC::Apply(position2);

	EXPECT_EQ(true, Vec3(-84, 84, 39) == position1);
	EXPECT_EQ(true, Vec3(84, -39, 39) == position2);
}