#pragma once

#include "common.hpp"

class EnergyData
{
public:
	int step_no;
	real TotalEnergy;
	real PotenEnergy;
	real PotEngyRepulsive;
	real PotEngyAttractive;
	real Pot_engy_balloon;
	real KineticEngy;
	real TotalEnergyMean;
	real TotalEnergyVariance;
	real TotalEnergyStdDev;

	EnergyData()
	{
		step_no=0;
		TotalEnergy=0;
		PotenEnergy = 0;
		PotEngyRepulsive = 0;
		PotEngyAttractive = 0;
		Pot_engy_balloon = 0;
		KineticEngy = 0;
		TotalEnergyMean = 0;
		TotalEnergyVariance = 0;
		TotalEnergyStdDev = 0;
	}
};
