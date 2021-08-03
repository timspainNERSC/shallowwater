/*
 * PGMWriter.hpp
 *
 *  Created on: 2 Aug 2021
 *      Author: Tim Spain
 */

#ifndef PGMWRITER_HPP
#define PGMWRITER_HPP

#include <string>
#include "ShallowWaterData.hpp"
#include "DoubleData2d.hpp"

class PGMWriter {
public:
	PGMWriter();

	static void writeSWD(int time, ShallowWaterData const& data);
	static void writeDD2(int time, std::string fieldName, DoubleData2d);

private:
	class Scaler {
	public:
		Scaler(double min, double max, int steps);
		const double min;
		const double max;
		const int steps;
		int stepFromValue(double value) const;
		double valueFromStep(int step) const;
	};
};

#endif /* PGMWRITER_HPP */
