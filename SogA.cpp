/*
 * SogA.cpp
 *
 *  Created on: 27 Jul 2021
 *      Author: work
 */

#include "SogA.hpp"

SogA::SogA():
SogA(0, 0, 1., 1.)
{ }

SogA::SogA(int nx, int ny, double delta_x, double delta_y):
	nx(nx), ny(ny), delta_x(delta_x), delta_y(delta_y),
	g(0.), f(0.),
	data(nx, ny)
{ }

void SogA::setF(double f)
{
	this->f = f;
}

void SogA::setG(double g)
{
	this->g = g;
}

void SogA::setData(ShallowWaterData &data)
{
	this->data = data;
}

ShallowWaterData SogA::getData()
{
	return data;
}

void SogA::iterate(double dt)
{
	DoubleData2d du_dx = dx(data.u);
	DoubleData2d du_dy = dy(data.u);

	DoubleData2d dv_dx = dx(data.v);
	DoubleData2d dv_dy = dy(data.v);

	DoubleData2d dh_dx = dx(data.h);
	DoubleData2d dh_dy = dy(data.h);

	DoubleData2d du_dt(nx, ny);
	DoubleData2d dv_dt(nx, ny);
	DoubleData2d dh_dt(nx, ny);

	// Calculate the time derivative of each variable
	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			du_dt(i, j) = -data.u(i, j) * du_dx(i, j)
					- data.v(i, j) * du_dy(i, j)
					+ this->f * data.v(i, j)
					- this->g * dh_dx(i, j);

			dv_dt(i, j) = -data.u(i, j) * dv_dx(i, j)
					- data.v(i, j) * dv_dy(i, j)
					- this->f * data.u(i, j)
					- this->g * dh_dy(i, j);

			dh_dt(i, j) = -data.u(i, j) * dh_dx(i, j)
					- data.v(i, j) * dh_dy(i, j)
					- data.h(i, j) * (du_dx(i, j) + dv_dy(i, j));
		}
	}

	// Integrate the equations over time
	integrate(data.u, du_dt, dt);
	integrate(data.v, dv_dt, dt);
	integrate(data.h, dh_dt, dt);
}

// x derivative. The grid is periodic in the x direction.
DoubleData2d SogA::dx(DoubleData2d const& argument)
{
	DoubleData2d derivative(nx, ny);

	double denominator = 0.5/delta_x;

	// Interior elements
	for (int i = 1; i < nx-1; i++) {
		for (int j = 0; j < ny; j++) {
			derivative(i, j) = (argument(i+1, j) - argument(i-1, j)) * denominator;
		}
	}

	// Edge columns
	for (int j = 0; j < ny; j++) {
		derivative(0, j) = (argument(1, j) - argument(nx-1, j)) * denominator;
		derivative(nx-1, j) = (argument(0, j) - argument(nx-2, j)) * denominator;
	}

	return derivative;
}

DoubleData2d SogA::dy(DoubleData2d const& argument)
{
	DoubleData2d derivative(nx, ny);

	double denominator = 0.5/delta_y;

	// Interior elements
	for (int i = 0; i < nx; i++) {
		for (int j = 1; j < ny-1; j++) {
			derivative(i, j) = (argument(i, j+1) - argument(i, j-1)) * denominator;
		}
	}

	denominator = 1./delta_y;

	for (int i = 0; i < nx; i++) {
		derivative(i, 0) = (argument(i, 1) - argument(i, 0)) * denominator;
		derivative(i, ny-1) = (argument(i, ny-1) - argument(i, ny-2)) * denominator;
	}

	return derivative;
}

DoubleData2d& SogA::integrate(DoubleData2d& variable, const DoubleData2d& derivative, double dt)
{

	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			variable(i, j) = derivative(i, j) * dt;
		}
	}

	return variable;
}
