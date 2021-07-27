/*
 * DoubleData2d.cpp
 *
 *  Created on: 26 Jul 2021
 *      Author: Tim Spain
 */

#include "DoubleData2d.hpp"

// Default constructor
DoubleData2d::DoubleData2d():
DoubleData2d(0,0)
{}

// Initialize to a given size
DoubleData2d::DoubleData2d(int nx, int ny):
		nx(nx), ny(ny)
{
	data.resize(nx, ny);
}

// Initialize with data
DoubleData2d::DoubleData2d(int nx, int ny, std::vector<double> const& data):
	DoubleData2d(nx, ny)
{
	setData(data);
}

// Copy constructor
DoubleData2d::DoubleData2d(DoubleData2d& source):
	DoubleData2d(source.nx, source.ny, source.data)
{ }

void DoubleData2d::setData(std::vector<double> const& data)
{
	this->data(data);
}

double& DoubleData2d::operator() (int i, int j)
{
	return data[ny*i + j];
}
