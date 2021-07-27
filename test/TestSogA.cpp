/*
 * TestSogA.cpp
 *
 *  Created on: 27 Jul 2021
 *      Author: Tim Spain
 */

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE( "Nominal test", "[example]") {
	std::cout << "Testing!" << std::endl;

	REQUIRE((2-1) == 1);
}


