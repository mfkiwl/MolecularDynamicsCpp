#pragma once

#include "common.hpp"

class EnergyData
{
public:
	int step_no;
	real TotalEnergy;
	real Poten_energy;
	real Pot_engy_repulsive;
	real Pot_engy_attractive;
	real Pot_engy_balloon;
	real Kinetic_engy;

	EnergyData()
	{
		step_no=0;
		TotalEnergy=0;
		Poten_energy = 0;
		Pot_engy_repulsive = 0;
		Pot_engy_attractive = 0;
		Pot_engy_balloon = 0;
		Kinetic_engy = 0;
	}
};
