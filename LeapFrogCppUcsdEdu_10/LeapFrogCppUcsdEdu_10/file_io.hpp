#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <fstream>
#include <iomanip>

#include "common.hpp"
#include "energy_data.hpp" 
#include "particle.hpp"

class FileIO
{
public:
	static void clearFile(const std::string& filename)
	{
		std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc); // Open the file in truncation mode

		if (!file.is_open())
		{
			std::cerr << "Error opening file!" << std::endl;
			return;
		}

		file.close(); // Close the file
	}

	static void writeTrajectoryToFile(const std::string& filename, const std::vector<Particle> particles)
	{
		int n_particles = particles.size();

		std::ofstream file(filename, std::ios_base::app); // Open the file in append mode

		if (file.is_open())
		{
			// Set the precision and fixed format for floating-point values
			file << std::fixed << std::setprecision(3);

			for (int i = 0; i < n_particles ; i++)
			{
				file
					<< std::setw(7) << particles[i].position.x << " "
					<< std::setw(7) << particles[i].position.y << " "
					<< std::setw(7) << particles[i].position.z << " "
					<< std::setw(10) << " ";
			}
			file << "\n";
			file.close();
			std::cout << "Trajectory saved to file: " << filename.c_str() << std::endl;
		}
		else
		{
			std::cout << "Unable to open the file: " << filename.c_str() << std::endl;
		}
	}

	static void writeEnergyToFile(const std::string& filename, const EnergyData& data)
	{
		std::ofstream file(filename, std::ios_base::app); // Open the file in append mode

		if (file.is_open())
		{
			// Write the row to the file
			file << std::fixed << std::setprecision(2) << data.TotalEnergy << ","
				<< std::fixed << std::setprecision(2) << data.TotalEnengyStats.getMean() << ","
				<< std::fixed << std::setprecision(2) << data.TotalEnengyStats.getVariance() << ","
				<< std::fixed << std::setprecision(2) << data.TotalEnengyStats.getStdDev() << ","

				 << std::fixed << std::setprecision(2) << data.PotenEnergy << ","
				<< std::fixed << std::setprecision(2) << data.PotenEnergyStats.getMean() << ","
				<< std::fixed << std::setprecision(2) << data.PotenEnergyStats.getVariance() << ","
				<< std::fixed << std::setprecision(2) << data.PotenEnergyStats.getStdDev() << ","

				 << std::fixed << std::setprecision(2) << data.PotEngyRepulsive << ","
				<< std::fixed << std::setprecision(2) << data.PotEngyRepulsiveStats.getMean() << ","
				<< std::fixed << std::setprecision(2) << data.PotEngyRepulsiveStats.getVariance() << ","
				<< std::fixed << std::setprecision(2) << data.PotEngyRepulsiveStats.getStdDev() << ","

				 << std::fixed << std::setprecision(2) << data.PotEngyAttractive << ","
				<< std::fixed << std::setprecision(2) << data.PotEngyAttractiveStats.getMean() << ","
				<< std::fixed << std::setprecision(2) << data.PotEngyAttractiveStats.getVariance() << ","
				<< std::fixed << std::setprecision(2) << data.PotEngyAttractiveStats.getStdDev() << ","

				 
				 << std::fixed << std::setprecision(2) << data.KineticEngy << ","
				<< std::fixed << std::setprecision(2) << data.KineticEngyStats.getMean() << ","
				<< std::fixed << std::setprecision(2) << data.KineticEngyStats.getVariance() << ","
				<< std::fixed << std::setprecision(2) << data.KineticEngyStats.getStdDev() << ","

				<< std::fixed << std::setprecision(2) << data.PotEngyBalloon << ","
				
				 << "\n";

			file.close();
			std::cout << "Energy saved to file: " << filename.c_str() << std::endl;
		}
		else
		{
			std::cout << "Unable to open the file: " << filename.c_str() << std::endl;
		}
	}
};
