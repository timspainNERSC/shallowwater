/*
 * TestPGMWriter.cpp
 *
 *  Created on: 3 Aug 2021
 *      Author: Tim Spain
 */

#define CATCH_CONFIG_MAIN

#include <cmath>
#include <fstream>
#include <catch2/catch.hpp>
#include "../DoubleData2d.hpp"
#include "../PGMWriter.hpp"

inline bool exists (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

TEST_CASE("Write data", "[PGMWriter]")
{
	// Create the data
	int nx = 15*15 + 1;
	int ny = 15*8 + 1;

	DoubleData2d data(nx, ny);
	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			data(i, j) = sqrt((double) (i*i + j*j));
		}
	}

	PGMWriter::writeDD2(0, "hyp", data);

	REQUIRE(exists("hyp.0.pgm"));

}


