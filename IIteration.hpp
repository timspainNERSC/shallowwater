/*
 * IIteration.hpp
 *
 *  Created on: 26 Jul 2021
 *      Author: Tim Spain
 */

#ifndef IITERATION_HPP
#define IITERATION_HPP

#include "ShallowWaterData.hpp"

// define the type of iterator that will be compiled
#if !defined(ITERATION_SOGA) && !defined(ITERATION_GOSA) && !defined(ITERATION_SOGB) && !defined(ITERATION_GOSB)
#define ITERATION_SOGA 1
#endif

#if defined ITERATION_GOSA
#include "GosA.hpp"
typedef GosA IterationProvider;
#elif defined ITERATION_SOGB
#include "SogB.hpp"
typedef SogB IterationProvider;
#elif defined ITERATION_GOSB
#include "GosB.hpp"
typedef GosB IterationProvider;
#elif defined ITERATION_SOGA
#include "SogA.hpp"
typedef SogA IterationProvider;
#endif

class IIteration {
public:
	// Create the iteration object with a certain size.
	IIteration(int nx, int ny, double delta_x, double delta_y):
		iterPro(nx, ny, delta_x, delta_y)
	{}

	void setF(double f) {iterPro.setF(f);}
	void setG(double g) {iterPro.setG(g);}
	void setData(ShallowWaterData &data) {iterPro.setData(data);}
	void iterate(double dt) {iterPro.iterate(dt);}
	ShallowWaterData getData( ) {return iterPro.getData();}
private:
	IterationProvider iterPro;
};

#endif /*def IITERATION_HPP */
