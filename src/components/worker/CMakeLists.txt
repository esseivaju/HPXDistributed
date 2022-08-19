add_library(Worker SHARED Worker.cpp)
target_link_libraries(Worker PUBLIC DataModel Algorithms HPX::hpx compile_features PRIVATE HPX::component HPX::iostreams_component)
target_include_directories(Worker INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)