#include "pch.h"
#include "header.h"
#include "../MolecularDynamicsCpp/pbc.hpp"
#include "../MolecularDynamicsCpp/pbc_static.hpp"

TEST(TestPBC, TestApply)
{
	PBC::boxLength = 90;

	Vec3 position1(45, 45, 45); PBC::Apply(position1);
	Vec3 position2(90, 90, 90); PBC::Apply(position2);
	Vec3 position3(-90, -90, -90); PBC::Apply(position3);
	Vec3 position4(0, 0, 0); PBC::Apply(position4);
	Vec3 position5(-1, -1, -1); PBC::Apply(position5);

	EXPECT_EQ(true, Vec3(45, 45, 45) == position1);
	EXPECT_EQ(true, Vec3(0, 0, 0) == position2);
	EXPECT_EQ(true, Vec3(0, 0, 0) == position3);
	EXPECT_EQ(true, Vec3(0, 0, 0) == position4);
	EXPECT_EQ(true, Vec3(89, 89, 89) == position5);
}