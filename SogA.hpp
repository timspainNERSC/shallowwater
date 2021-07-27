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

	SogA(int nx, int ny, double delta_x, double delta_y);

	void setF(double f);
	void setG(double g);
	void setData(ShallowWaterData &data);
	void iterate(double dt);
	ShallowWaterData getData( );

private:
	int nx;
	int ny;

	double delta_x;
	double delta_y;

	double f;
	double g;
	ShallowWaterData data;

	DoubleData2d dx(DoubleData2d const& argument);
	DoubleData2d dy(DoubleData2d const& argument);

	void integrate(DoubleData2d& variable, DoubleData2d const& derivative, double dt);
};

#endif /*ndef SOGA_HPP */
