/*
 * ElementData.hpp
 *
 *  Created on: 28 Jul 2021
 *      Author: Tim Spain
 */

#ifndef ELEMENTDATA_HPP
#define ELEMENTDATA_HPP

#include "DoubleDeriv.hpp"

struct ElementData {
public:
	ElementData();
	ElementData(double u, double v, double h);
	DoubleDeriv u;
	DoubleDeriv v;
	DoubleDeriv h;
	void iterate(double dt);

	static void setF(double fin);
	static void setG(double gin);
private:
	static double f;
	static double g;
};

#endif /* ELEMENTDATA_HPP */
