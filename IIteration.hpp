/*
 * IIteration.hpp
 *
 *  Created on: 26 Jul 2021
 *      Author: Tim Spain
 */

#ifndef IITERATION_HPP
#define IITERATION_HPP

#include "ShallowWaterData.hpp"

class IIteration {
public:
	// Create the iteration object with a certain size.
	IIteration(int nx, int ny);

	void setF(double f);
	void setG(double g);
	void setData(ShallowWaterData &);
	void iterate(double dt);
	ShallowWaterData getData( );
};

#endif /*def IITERATION_HPP */
