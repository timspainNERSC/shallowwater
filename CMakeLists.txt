cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)

project(shallowwater)

set( CMAKE_VERBOSE_MAKEFILE on )

find_package(netCDF REQUIRED)
find_package(Catch2 REQUIRED)

add_executable(hello hello.cpp)
target_include_directories(hello PUBLIC ${netCDF_INCLUDE_DIR})
target_link_directories(hello PUBLIC ${netCDF_LIB_DIR})
target_link_libraries(hello LINK_PUBLIC netcdf-cxx4)

set(ShallowWaterSources
	"main.cpp"
	"DoubleData2d.cpp"
	"ShallowWaterData.cpp"
	"SogA.cpp"
	)

add_executable(shallowwater ${ShallowWaterSources})

# Testing
add_executable(testsoga
	test/TestSogA.cpp
	SogA.cpp
	ShallowWaterData.cpp
	DoubleData2d.cpp)

target_link_libraries(testsoga PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(testsoga)