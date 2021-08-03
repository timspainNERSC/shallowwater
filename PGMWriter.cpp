/*
 * PGMWriter.cpp
 *
 *  Created on: 2 Aug 2021
 *      Author: Tim Spain
 */

#include "PGMWriter.hpp"

#include <iostream>
#include <fstream>
#include <utility>

PGMWriter::PGMWriter() {
}

void PGMWriter::writeSWD(int time, ShallowWaterData const& data)
{
	writeDD2(time, "u", data.u);
	writeDD2(time, "v", data.v);
	writeDD2(time, "h", data.h);

}

void PGMWriter::writeDD2(int time, std::string fieldName, DoubleData2d data)
{
	std::ofstream pgm(fieldName + "." + std::to_string(time) + "." + "pgm", std::ios::binary);
	pgm << "P2" << "\n"; // Separator is explicitly a new line, not std::endl;

	// Gather maximum and minimum
	std::pair<double, double> minmax = data.range();

	const int steps = 255;
	Scaler scaler(minmax.first, minmax.second, steps);

	// Comment giving the scaling
	pgm << "# 0 = " << minmax.first << ", 255 = " << minmax.second << ". range 0–" << steps << "\n";

	// Size of the image
	std::pair<int, int> size = data.gridSize();
	pgm << size.first << " " << size.second << "\n";

	// Maximum value
	pgm << steps << "\n";

	// Have to reverse iteration order here
	for (int j = 0; j < size.second; j++) {
		for (int i = 0; i < size.first; i++) {
			pgm << scaler.stepFromValue(data(i, j)) << " ";
		}
		pgm << "\n";
	}

	pgm.close();
}

PGMWriter::Scaler::Scaler(double min, double max, int steps):
min(min), max(max), steps(steps)
{ }

int PGMWriter::Scaler::stepFromValue(double value) const
{
	return (value - min) / (max - min) * steps;
}

double PGMWriter::Scaler::valueFromStep(int step) const
{
	return ((max - min) * step) / steps + min;
}
