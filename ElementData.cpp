/*
 * ElementData.cpp
 *
 *  Created on: 28 Jul 2021
 *      Author: work
 */

#include "ElementData.hpp"

ElementData::ElementData() :
ElementData(0., 0., 0.)
{ }

ElementData::ElementData(double u, double v, double h) :
u(u), v(v), h(h)
{ }

void ElementData::iterate(double dt)
{
	double du_dt = - u * u.d_dx
			- v * u.d_dy
			+ f * v
			- g * h.d_dx;

	double dv_dt = - u * v.d_dx
			- v * v.d_dy
			- f * u
			- g * h.d_dy;

	double dh_dt = - u * h.d_dx
			- v * h.d_dy
			- h * (u.d_dx + v.d_dy);

	u += du_dt * dt;
	v += dv_dt * dt;
	h += dh_dt * dt;

}
