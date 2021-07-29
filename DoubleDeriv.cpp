/*
 * DoubleDeriv.cpp
 *
 *  Created on: 28 Jul 2021
 *      Author: Tim Spain
 */

#include "DoubleDeriv.hpp"

DoubleDeriv::DoubleDeriv():
value(0.), d_dx(0.), d_dy(0.)
{ }

DoubleDeriv::DoubleDeriv(const double& x) :
value(x), d_dx(0.), d_dy(0.)
{ }

DoubleDeriv::operator double() const
{
	return value;
}

double& DoubleDeriv::setXDeriv(const double& x)
{
	return d_dx = x;
}

double DoubleDeriv::xDeriv( )
{
	return d_dx;
}

double& DoubleDeriv::setYDeriv(const double& y)
{
	return d_dy = y;
}

double DoubleDeriv::yDeriv( )
{
	return d_dy;
}

DoubleDeriv& DoubleDeriv::operator+=(const double& addend)
{
	value += addend;
	return *this;
}

DoubleDeriv& DoubleDeriv::operator+=(const DoubleDeriv& addend)
{
	value += addend.value;
	return *this;
}
