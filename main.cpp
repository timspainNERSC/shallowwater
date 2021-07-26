/*
 * main.cpp
 *
 *  Created on: 26 Jul 2021
 *      Author: Tim Spain
 */

#include <iostream>
#include "IIteration.hpp"
#include "ShallowWaterData.hpp"

int main( ) {
	// Hardcoded physical grid dimensions
	double lx = 1e6;
	double ly = 1e6;

	// Read array dimensions from stdin
	int nx;
	int ny;
	std::cin >> nx >> ny;

	IIteration iteration(nx, ny);

	// Fill the physical constants
	double g = 9.80665; // m s⁻²
	double f = 7.292116e-5; // rad s⁻¹
	iteration.setF(f);
	iteration.setG(g);

	double dx = lx / (nx - 1);
	double dy = ly / (ny - 1);

	ShallowWaterData swd(nx, ny);
	// Fill the constant eastward wind data
	// u = u0
	// v = 0
	// h = -f u0 y / g
	double u0 = 5.0; // m s⁻¹
	double h0 = - f * u0 / g;

	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			swd.u(i, j) = u0;
			swd.v(i, j) = 0.;
			swd.h(i, j) = h0 * (-1 * j * dy);
		}
	}
	iteration.setData(swd);

	// Hard-coded duration and time step
	double dt = 100.;
	double lt = 1e7; // 115.7 days

	for (double t = 0.0; t < lt; t += dt) {
		iteration.iterate(dt);
	}

	ShallowWaterData result = iteration.getData();
}


