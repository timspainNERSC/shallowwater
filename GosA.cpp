/*
 * GosA.cpp
 *
 *  Created on: 28 Jul 2021
 *      Author: Tim Spain
 */

#include <stdexcept>
#include <sstream>
#include "GosA.hpp"

GosA::GosA():
GosA(1, 1, 0., 0.)
{ }

GosA::GosA(int nx, int ny, double delta_x, double delta_y) :
nx(nx), ny(ny), delta_x(delta_x), delta_y(delta_y),
f(0.), g(0.),
data(nx*ny)
{ }

void GosA::setF(double f)
{
	this->f = f;
}

void GosA::setG(double g)
{
	this->g = g;
}

void GosA::setData(ShallowWaterData& data)
{
	ElementData::setF(this->f);
	ElementData::setG(this->g);

	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			ElementData* pEl = &this->data[i*ny + j];
			pEl->u = data.u(i, j);
			pEl->v = data.v(i, j);
			pEl->h = data.h(i, j);
		}
	}
}

ShallowWaterData GosA::getData()
{
	ShallowWaterData out(nx, ny);

	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			ElementData* pEl = &this->data[i*ny + j];
			out.u(i, j) = pEl->u;
			out.v(i, j) = pEl->v;
			out.h(i, j) = pEl->h;
		}
	}
	return out;
}

double basicDerivative(double rhValue, double lhValue, double denominator) {
	return (rhValue - lhValue) / denominator;
}

void basicDerivativesX(ElementData* left, ElementData* here, ElementData* right, double delta_x)
{
	here->u.d_dx = basicDerivative(right->u, left->u, 2*delta_x);
	here->v.d_dx = basicDerivative(right->v, left->v, 2*delta_x);
	here->h.d_dx = basicDerivative(right->h, left->h, 2*delta_x);
}

void basicDerivativesY(ElementData* below, ElementData* here, ElementData* above, double delta_y)
{
	here->u.d_dy = basicDerivative(below->u, above->u, 2*delta_y);
	here->v.d_dy = basicDerivative(below->v, above->v, 2*delta_y);
	here->h.d_dy = basicDerivative(below->h, above->h, 2*delta_y);
}

void GosA::iterate(double dt)
{
	// derivatives
	// x
	// wraparound columns
	for (int j = 0; j < ny; j++) {
		ElementData* last_col = &data[indexer(nx - 1, j)];
		ElementData* first_col = &data[indexer(0, j)];

		basicDerivativesX(last_col, first_col, &data[indexer(1, j)], delta_x);
		basicDerivativesX(&data[indexer(nx-2, j)], last_col, first_col, delta_x);
	}

	// bulk data
	for (int i = 1; i < nx-1; i++) {
		for (int j = 0; j < ny; j++) {
			basicDerivativesX(&data[indexer(i-1, j)],
					&data[indexer(i, j)],
					&data[indexer(i+1, j)],
					delta_x);
		}
	}

	// y
	for (int i = 0; i < nx; i++) {
		// top edge
		basicDerivativesY(&data[indexer(i, 0)],
					&data[indexer(i, 0)],
					&data[indexer(i, 1)],
					delta_y/2);
		// bulk data
		for (int j = 1; j < ny-1; j++) {
			basicDerivativesY(&data[indexer(i, j-1)],
						&data[indexer(i, j)],
						&data[indexer(i, j+1)],
						delta_y);
		}
		// bottom edge
		basicDerivativesY(&data[indexer(i, ny-2)],
					&data[indexer(i, ny-1)],
					&data[indexer(i, ny-1)],
					delta_y/2);
	}

	// loop over every element, calculate and integrate
	for (auto iter = data.begin(); iter != data.end(); iter++) {
		iter->iterate(dt);
	}
}

int GosA::indexer(int i, int j) {
	if ( (i < 0) || (i >= nx) ) {
		std::stringstream eText;
		eText << "Index i out of range: i=" << i << ". Valid range 0.." << nx-1;
		throw std::out_of_range(eText.str());
	}
	if ( (j < 0) || (j >= ny) ) {
		std::stringstream eText;
		eText << "Index j out of range: j=" << j << ". Valid range 0.." << ny-1;
		throw std::out_of_range(eText.str());
	}
	return i * ny + j;
}
