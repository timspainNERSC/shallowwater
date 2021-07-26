cmake_minimum_required(VERSION 3.0.0)
project(shallowwater)

set( CMAKE_VERBOSE_MAKEFILE on )

find_package(netCDF REQUIRED)

add_executable(shallowwater hello.cpp)
target_include_directories(shallowwater PUBLIC ${netCDF_INCLUDE_DIR})
target_link_directories(shallowwater PUBLIC ${netCDF_LIB_DIR})
target_link_libraries(shallowwater LINK_PUBLIC netcdf-cxx4)
