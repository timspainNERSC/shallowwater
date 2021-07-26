/*
 * ShallowWaterData.hpp
 *
 *  Created on: 26 Jul 2021
 *      Author: Tim Spain
 */

#ifndef SHALLOWWATERDATA_HPP
#define SHALLOWWATERDATA_HPP

#include <DoubleData2d.hpp>

class ShallowWaterData {
public:
	ShallowWaterData(int nx, int ny);

	DoubleData2d u;
	DoubleData2d v;
	DoubleData2d h;
};

#endif /*ndef SHALLOWWATERDATA_HPP */
