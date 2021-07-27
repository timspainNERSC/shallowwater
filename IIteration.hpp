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
#include "gosa.hpp"
typedef GosA IterationProvider;
#elif defined ITERATION_SOGB
#include "sogb.hpp"
typedef SogB IterationProvider;
#elif defined ITERATION_GOSB
#include "gosb.hpp"
typedef GosB IterationProvider;
#elif defined ITERATION_SOGA
#include "soga.hpp"
typedef SogA IterationProvider;
#endif

class IIteration {
public:
	// Create the iteration object with a certain size.
	IIteration(int nx, int ny):
		iterPro(nx, ny)
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
