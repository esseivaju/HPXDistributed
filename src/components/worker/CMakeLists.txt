add_library(Worker SHARED Worker.cpp)
target_link_libraries(Worker PUBLIC HPX::hpx compile_features)
target_include_directories(Worker INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)