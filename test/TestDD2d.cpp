/*
 * TestDD2d.cpp
 *
 *  Created on: 28 Jul 2021
 *      Author: Tim Spain
 */

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <stdexcept>
#include "../DoubleData2d.hpp"

TEST_CASE( "Creation and indexing test", "[DoubleData2d]")
{
	int nx = 2;
	int ny = 3;
	DoubleData2d data(nx, ny);

	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			CHECK_NOTHROW(data(i,j));
		}
	}

	REQUIRE_THROWS_AS(data(nx, 0), std::out_of_range);
	REQUIRE_THROWS_AS(data(0, ny), std::out_of_range);

}

TEST_CASE( "Read/write test", "[DoubleData2d]")
{
	int nx = 10;
	int ny = 5;

	DoubleData2d data(nx, ny);
	int i = 3;
	int j = 4;

	double initial_value = data(i, j);

	double set = 0x3.243F6A8885A308D31319p0 + initial_value;

	data(i, j) = set;

	REQUIRE(data(i,j) != initial_value);
	REQUIRE(data(i, j) == set);
	REQUIRE(set != initial_value);
}

