/*
 * main.cpp
 *
 *  Created on: 26 Jul 2021
 *      Author: Tim Spain
 */

#include <iostream>
#include <cmath>
#include "IIteration.hpp"
#include "ShallowWaterData.hpp"
#include "PGMWriter.hpp"

int main( ) {
	// Hardcoded physical grid dimensions
	double lx = 1e6;
	double ly = 1e6;

	// Read array dimensions from stdin
	int nx;
	int ny;
	std::cin >> nx >> ny;

	double dx = lx / (nx - 1);
	double dy = ly / (ny - 1);

	IIteration iteration(nx, ny, dx, dy);

	// Fill the physical constants
	double g = 9.80665; // m s⁻²
	double f = 7.292116e-5; // rad s⁻¹
	iteration.setF(f);
	iteration.setG(g);


	ShallowWaterData swd(nx, ny);
	// Fill the constant eastward wind data
	// u = u0
	// v = 0
	// h = -f u0 y / g
	double u0 = 5.0; // m s⁻¹
	double h0 = - f * u0 / g;

	// Geopotential blob, not in balance
	double h1 = 10.; // m
	double x0 = nx / 2.;
	double y0 = ny / 2.;
	double r0 = 5.;

	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			swd.u(i, j) = u0;
			swd.v(i, j) = 0.;
			swd.h(i, j) = h1 * (-1 * j * dy);
			double r = (i - x0) * (i - x0) + (j - y0) * (j - y0);
			if (r <= r0) {
				swd.h(i, j) += h1 * sqrt(1. - r/r0);
			}
		}
	}
	iteration.setData(swd);

	// Hard-coded duration and time step
	double dt = 100.;
	double lt = 1000; // 115.7 days

	PGMWriter::writeSWD(0, swd);
	const double writeInterval = 1 * dt;
	double last_write_t = 0.;

	for (double t = 0.0; t < lt; t += dt) {
		if (t - last_write_t >= writeInterval) {
			PGMWriter::writeSWD(t, iteration.getData());
			last_write_t = t;
		}
		iteration.iterate(dt);
	}

	ShallowWaterData result = iteration.getData();
	PGMWriter::writeSWD(lt, result);
}


