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
target_link_libraries(HPXDistributed Scheduler Algorithms DataModel HPX::hpx HPX::wrap_main HPX::iostreams_component compile_features)

add_executable(Demo src/demo.cpp)

option(SINGLE_ARG "Pass a single argument to remote action invocation" OFF)
option(VECTOR_2ND_ARG "2nd argument to remote call is a vector. Has en effect only when SINGLE_ARG=OFF" OFF)
option(DEFAULT_CONSTRUCTIBLE "EventContext is default constructible" OFF)
if(SINGLE_ARG AND VECTOR_2ND_ARG)
    message(WARNING "Setting VECTOR_2ND_ARG with SINGLE_ARG has no effect")
endif()
if(SINGLE_ARG)
    target_compile_definitions(Demo PRIVATE "SINGLE_ARG")
endif()
if(VECTOR_2ND_ARG)
    target_compile_definitions(Demo PRIVATE "VECTOR_2ND_ARG")
endif()
if(DEFAULT_CONSTRUCTIBLE)
    target_compile_definitions(Demo PRIVATE "DEFAULT_CONSTRUCTIBLE")
endif()

target_link_libraries(Demo HPX::hpx HPX::wrap_main HPX::iostreams_component compile_features)