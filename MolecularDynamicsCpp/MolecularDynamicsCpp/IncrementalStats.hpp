#pragma once

#include <iostream>
#include <cmath>

class IncrementalStats 
{
private:
	int count;
	double mean;
	double variance;
	double squared_mean;

public:
	IncrementalStats() : count(0), mean(0.0), variance(0.0), squared_mean(0.0) {}

	void update(double x) 
	{
		count++;
		double delta = x - mean;
		mean += delta / count;
		double delta2 = x - mean;
		variance += delta * delta2;
		squared_mean += x * x;
	}

	double getMean() const {
		return mean;
	}

	double getVariance() const {
		return variance / count;
	}

	double getStdDev() const {
		return std::sqrt(getVariance());
	}
};

//int main() {
//	IncrementalStats stats;
//
//	// Example usage
//	stats.update(5.0);
//	stats.update(10.0);
//	stats.update(15.0);
//
//	std::cout << "Mean: " << stats.getMean() << std::endl;
//	std::cout << "Variance: " << stats.getVariance() << std::endl;
//	std::cout << "Standard Deviation: " << stats.getStandardDeviation() << std::endl;
//
//	return 0;
//}