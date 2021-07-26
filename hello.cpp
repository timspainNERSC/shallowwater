#include <iostream>
#include <netcdf>

// We are writing 2D data, a 6 x 12 grid.
static const int NX = 6;
static const int NY = 12;

int main( ) {

	int data[NX][NY];

	netCDF::NcFile file;
	std::cout << "Hello, world!" << std::endl;
	return 0;
}
