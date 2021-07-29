/*
 * DoubleDeriv.hpp
 *
 *  Created on: 28 Jul 2021
 *      Author: Tim Spain
 */

#ifndef DOUBLEDERIV_HPP
#define DOUBLEDERIV_HPP

class DoubleDeriv {
public:
	DoubleDeriv();
	DoubleDeriv(const double& x);
	operator double() const;
	double xDeriv();
	double yDeriv();
	double& setXDeriv(const double&);
	double& setYDeriv(const double&);

	DoubleDeriv& operator+=(const double&);
	DoubleDeriv& operator+=(const DoubleDeriv&);
private:
	double value;
public:
	double d_dx;
	double d_dy;
};

#endif /* DOUBLEDERIV_HPP */
