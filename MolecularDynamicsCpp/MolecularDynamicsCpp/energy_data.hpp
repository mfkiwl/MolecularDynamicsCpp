#pragma once

#include "common.hpp"
#include "IncrementalStats.hpp"

class EnergyData
{
public:
	int count;
	int step_no;
	real TotalEnergy;
	real PotenEnergy;
	real PotEngyRepulsive;
	real PotEngyAttractive;
	real PotEngyBalloon;
	real KineticEngy;

	IncrementalStats TotalEnengyStats;
	IncrementalStats PotenEnergyStats;
	IncrementalStats PotEngyRepulsiveStats;
	IncrementalStats PotEngyAttractiveStats;
	IncrementalStats KineticEngyStats;

	EnergyData()
	{
		count = 0;
		step_no = 0;
		TotalEnergy = 0;
		PotenEnergy = 0;
		PotEngyRepulsive = 0;
		PotEngyAttractive = 0;
		PotEngyBalloon = 0;
		KineticEngy = 0;
	}

	void update(const EnergyData& other)
	{
		*this = other;
		TotalEnengyStats.update(other.TotalEnergy);
		PotenEnergyStats.update(other.PotenEnergy);
		PotEngyRepulsiveStats.update(other.PotEngyRepulsive);
		PotEngyAttractiveStats.update(other.PotEngyAttractive);
		KineticEngyStats.update(other.KineticEngy);
	}

	// Copy constructor
	EnergyData(const EnergyData& other)
	{
		step_no = other.step_no;
		count = other.count;
		TotalEnergy = other.TotalEnergy;
		PotenEnergy = other.PotenEnergy;
		PotEngyRepulsive = other.PotEngyRepulsive;
		PotEngyAttractive = other.PotEngyAttractive;
		PotEngyBalloon = other.PotEngyBalloon;
		KineticEngy = other.KineticEngy;
	}

	// Copy assignment operator
	EnergyData& operator=(const EnergyData& other)
	{
		if (this != &other)
		{
			step_no = other.step_no;
			count = other.count;
			TotalEnergy = other.TotalEnergy;
			PotenEnergy = other.PotenEnergy;
			PotEngyRepulsive = other.PotEngyRepulsive;
			PotEngyAttractive = other.PotEngyAttractive;
			PotEngyBalloon = other.PotEngyBalloon;
			KineticEngy = other.KineticEngy;
		}

		return *this;
	}
};