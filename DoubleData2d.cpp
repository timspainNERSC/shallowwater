/*
 * DoubleData2d.cpp
 *
 *  Created on: 26 Jul 2021
 *      Author: Tim Spain
 */

#include <stdexcept>
#include <sstream>
#include "DoubleData2d.hpp"

// Default constructor
DoubleData2d::DoubleData2d():
DoubleData2d(0,0)
{}

// Initialize to a given size
DoubleData2d::DoubleData2d(int nx, int ny):
		nx(nx), ny(ny)
{
	data.resize(nx*ny);
}

// Initialize with data
DoubleData2d::DoubleData2d(int nx, int ny, std::vector<double> const& data):
	DoubleData2d(nx, ny)
{
	setData(data);
}

// Copy constructor
DoubleData2d::DoubleData2d(const DoubleData2d& source):
	DoubleData2d(source.nx, source.ny, source.data)
{ }

void DoubleData2d::setData(std::vector<double> const& data)
{
	this->data = data;
}

double& DoubleData2d::operator() (int i, int j)
{
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
	return data[ny*i + j];
}

double DoubleData2d::operator() (int i, int j) const
{
	return data[ny*i + j];
}
