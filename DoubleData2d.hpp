/*
 * DoubleData2d.hpp
 *
 *  Created on: 26 Jul 2021
 *      Author: Tim Spain
 */

#ifndef DOUBLEDATA2D_HPP
#define DOUBLEDATA2D_HPP

#include <vector>

class DoubleData2d {
public:
	// Default array size is 0
	DoubleData2d();
	DoubleData2d(int nx, int ny);
	// Initialize with data
	DoubleData2d(int nx, int ny, std::vector<double> const& data);
	// Copy constructor
	DoubleData2d(const DoubleData2d& source);

	void setData(std::vector<double> const& data);

	double& operator() (int i, int j);
private:
	int nx;
	int ny;
	
	std::vector<double> data;
	
};



#endif /* DOUBLEDATA2D_HPP */
