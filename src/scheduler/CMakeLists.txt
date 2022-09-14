add_library(Scheduler SHARED Scheduler.cpp)
target_link_libraries(Scheduler PUBLIC HPX::hpx compile_features Worker DataModel PRIVATE HPX::iostreams_component)
target_include_directories(Scheduler INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)