/*
 * TestDoubleDeriv.cpp
 *
 *  Created on: 28 Jul 2021
 *      Author: Tim Spain
 */

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "../DoubleDeriv.hpp"

TEST_CASE("Assignment and retrieval of main element", "[DoubleDeriv]")
{
	DoubleDeriv u;

	double initial_value = u;
	double set = 0x3.243F6A8885A308D31319p0 + initial_value;
	u = set;
	double get = u;

	REQUIRE(get == set);
	REQUIRE(get != initial_value);
	REQUIRE(set != initial_value);
}

TEST_CASE("Assignment and retrieval of x derivative", "[DoubleDeriv]")
{
	DoubleDeriv u = 2.34567890;
	double xD = 1.2987654;
	u.setXDeriv(xD);
	double get = u.xDeriv();

	REQUIRE(get == xD);
	REQUIRE(u.d_dx == xD);

	xD = -6578.08786;
	double pass = u.setXDeriv(xD);
	get = u.xDeriv();
	REQUIRE(get == xD);
	REQUIRE(get == pass);
}

TEST_CASE("Assignment and retrieval of y derivative", "[DoubleDeriv]")
{
	DoubleDeriv u = 2.34567890;
	double yD = 1.2987654;
	u.setYDeriv(yD);
	double get = u.yDeriv();

	REQUIRE(get == yD);
	REQUIRE(u.d_dy == yD);

	yD = -6578.08786;
	double pass = u.setYDeriv(yD);
	get = u.yDeriv();
	REQUIRE(get == yD);
	REQUIRE(get == pass);
}
