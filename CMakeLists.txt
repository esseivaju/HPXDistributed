cmake_minimum_required(VERSION 3.17)

project(HPXDistributed CXX)

find_package(HPX REQUIRED)

add_library(compile_features INTERFACE)
target_compile_features(compile_features INTERFACE cxx_std_20)

add_subdirectory(src/algorithms)
add_subdirectory(src/datamodel)
add_subdirectory(src/components)
add_subdirectory(src/scheduler)

add_executable(HPXDistributed src/main.cpp)

option(SINGLE_WORKER "Instantiate only a single worker" OFF)
if(SINGLE_WORKER)
    target_compile_definitions(Scheduler PRIVATE "SINGLE_WORKER")
endif()


target_link_libraries(HPXDistributed Scheduler Algorithms DataModel HPX::hpx HPX::wrap_main HPX::iostreams_component compile_features)