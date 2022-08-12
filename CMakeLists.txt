cmake_minimum_required(VERSION 3.17)

project(HPXDistributed CXX)

find_package(HPX REQUIRED)
find_package(Boost REQUIRED)
find_package(fmt)

add_library(compile_features INTERFACE)
target_compile_features(compile_features INTERFACE cxx_std_20)

add_subdirectory(src/datamodel)
add_subdirectory(src/components)
add_subdirectory(src/scheduler)

add_executable(HPXDistributed src/main.cpp)
target_link_libraries(HPXDistributed Scheduler DataModel HPX::hpx HPX::wrap_main Boost::boost fmt::fmt HPX::iostreams_component compile_features)