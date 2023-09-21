#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <graph/Graph.h>

namespace BellmanFord {
std::string traverse(const Graph<char>& graph, char root, char goal);

};

#endif // BELLMANFORD_H
