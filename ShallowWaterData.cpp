/*
 * ShallowWaterData.cpp
 *
 *  Created on: 27 Jul 2021
 *      Author: Tim Spain
 */

#include "ShallowWaterData.hpp"

ShallowWaterData::ShallowWaterData(int nx, int ny) :
u(nx, ny), v(nx, ny), h(nx, ny)
{ }

