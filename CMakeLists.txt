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

set(CommonSources
	"main.cpp"
	"ShallowWaterData.cpp"
	"DoubleData2d.cpp"
	)
	
set(SogaSources
	${CommonSources}
	"SogA.cpp"
	)

add_executable(soga ${SogaSources})
target_compile_definitions(soga PRIVATE ITERATION_SOGA=1)

set(GosaSources
	${CommonSources}
	"Gosa.cpp"
	"ElementData.cpp"
	"DoubleDeriv.cpp"
	)

add_executable(gosa ${GosaSources})
target_compile_definitions(gosa PRIVATE ITERATION_GOSA=1)

# Testing
add_executable(testsoga
	test/TestSogA.cpp
	SogA.cpp
	ShallowWaterData.cpp
	DoubleData2d.cpp)

target_link_libraries(testsoga PRIVATE Catch2::Catch2)

add_executable(testdd2d
	test/TestDD2d.cpp
	DoubleData2d.cpp)

target_link_libraries(testdd2d PRIVATE Catch2::Catch2)

add_executable(testdoublederiv
	test/TestDoubleDeriv.cpp
	DoubleDeriv.cpp)

target_link_libraries(testdoublederiv PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(testsoga)