# implementations of graph algorithms
project(graph_alg)

# template class for constructing generic graphs. dont touch this
add_library(graph "${PROJECT_SOURCE_DIR}/../include/graph/Graph.h")
target_include_directories(graph PUBLIC ${PROJECT_SOURCE_DIR}/../include)

# BFS
# duplicate this when adding a new algorithm
add_library(BFS "${PROJECT_SOURCE_DIR}/../include/BFS.h" "${PROJECT_SOURCE_DIR}/../src/BFS.cpp")
target_include_directories(BFS PUBLIC ${PROJECT_SOURCE_DIR}/../include)


target_link_libraries(graph BFS)