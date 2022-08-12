add_library(Algorithms SHARED Algorithm.cpp AlgorithmA.cpp AlgorithmA.h AlgorithmB.cpp AlgorithmB.h AlgorithmC.cpp AlgorithmC.h AlgorithmD.cpp AlgorithmD.h)
target_link_libraries(Algorithms PUBLIC compile_features DataModel)
target_include_directories(Algorithms INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)