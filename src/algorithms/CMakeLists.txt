add_library(Algorithms SHARED Algorithm.cpp AlgorithmA.cpp AlgorithmB.cpp AlgorithmC.cpp AlgorithmD.cpp AlgorithmE.cpp)
target_link_libraries(Algorithms PUBLIC compile_features DataModel PRIVATE Eigen3::Eigen HPX::iostreams_component)
target_include_directories(Algorithms INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)