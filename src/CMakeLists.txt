# implementations of graph algorithms
project(graph_alg)

# template class for constructing generic graphs. dont touch this
add_library(graph "${PROJECT_SOURCE_DIR}/../include/graph/Graph.h")

# some utils
add_library(utils INTERFACE "${PROJECT_SOURCE_DIR}/../include/utils/Debug.h")


# breadth-first
# duplicate this when adding a new algorithm
add_library(BFS "${PROJECT_SOURCE_DIR}/../include/BFS.h" "${PROJECT_SOURCE_DIR}/../src/BFS.cpp")
target_include_directories(BFS PUBLIC ${PROJECT_SOURCE_DIR}/../include)

# depth-first
add_library(DFS "${PROJECT_SOURCE_DIR}/../include/DFS.h" "${PROJECT_SOURCE_DIR}/../src/DFS.cpp")
target_include_directories(DFS PUBLIC ${PROJECT_SOURCE_DIR}/../include)

# dijkstra
add_library(dijkstra "${PROJECT_SOURCE_DIR}/../include/Dijkstra.h" "${PROJECT_SOURCE_DIR}/../src/Dijkstra.cpp")
target_include_directories(dijkstra PUBLIC ${PROJECT_SOURCE_DIR}/../include)

target_link_libraries(
    graph
    BFS
    DFS
    dijkstra
)