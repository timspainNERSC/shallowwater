/*
 * GosA.hpp
 *
 *  Created on: 28 Jul 2021
 *      Author: Tim Spain
 */

#ifndef GOSA_HPP
#define GOSA_HPP

#include <vector>
#include "ShallowWaterData.hpp"
#include "ElementData.hpp"

class GosA {
public:
	GosA();

	GosA(int nx, int ny, double delta_x, double delta_y);

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

	std::vector<ElementData> data;

	int indexer(int i, int j);
};

#endif /*ndef GOSA_HPP */
