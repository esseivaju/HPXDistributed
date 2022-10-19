add_library(DataModel SHARED EventContext.cpp)
target_link_libraries(DataModel PUBLIC HPX::hpx Eigen3::Eigen compile_features)
target_include_directories(DataModel INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)