cmake_minimum_required(VERSION 3.0.0)
project(shallowwater)

find_package(NetCDF REQUIRED)

add_executable(shallowwater hello.cpp)
target_link_libraries(shallowwater LINK_PUBLIC ${NETCDF_LIBRARIES_C})
