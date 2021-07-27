/*
 * SogA.cpp
 *
 *  Created on: 27 Jul 2021
 *      Author: work
 */

#include "SogA.hpp"

SogA::SogA():
SogA(0, 0)
{ }

SogA::SogA(int nx, int ny):
	nx(nx), ny(ny), g(0.), f(0.)
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
	this->data(data);
}

ShallowWaterData SogA::getData()
{
	return data;
}

