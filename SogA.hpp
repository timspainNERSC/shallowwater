/*
 * SogA.hpp
 *
 *  Created on: 27 Jul 2021
 *      Author: Tim Spain
 */

#ifndef SOGA_HPP
#define SOGA_HPP

#include "ShallowWaterData.hpp"

class SogA {
public:
	SogA();

	SogA(int nx, int ny);

	void setF(double f);
	void setG(double g);
	void setData(ShallowWaterData &data);
	void iterate(double dt);
	ShallowWaterData getData( );

private:
	int nx;
	int ny;
	double f;
	double g;
	ShallowWaterData data;

};

#endif /*ndef SOGA_HPP */
