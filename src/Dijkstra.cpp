#include <graph/Graph.h>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
//
// Dijkstra(G, root, goal)
//  for each v in graph
//      dist[v] = infinity
//      add v to queue
//
//  dist[root] = 0
//  while queue is not empty
//      u = v in queue with minimum dist[u]
//      remove u from queue
//
//      for each neighbor v of u still in queue
//          alt = dist[u] + edges(u,v)
//          if alt < dist[v]
//              dist[v] = alt
//              prev[v] = u
//
namespace Dijkstra {
std::string traverse(const Graph<char>& graph, char root, char goal)
{

    if (!graph.getIsWeighted()) {
        std::cout << "Graph is not weighted. Not using Dijkstra's" << std::endl;
        return "";
    }

    std::queue<std::pair<double, char>> queue;
    std::set<char> visited;
    std::unordered_map<char, char> parent;
    std::unordered_map<char, double> dist;
    std::vector<char> nodes = graph.getNodes();

    for (const auto& entry : nodes) {
        dist[entry] = std::numeric_limits<double>::infinity();
    }

    dist[root] = 0.0;
    queue.push({ 0.0, root });

    while (!queue.empty()) {
        // get the node with the minimum distance
        char current_node = queue.front().second;
        queue.pop();

        if (current_node == goal) {
            std::vector<char> path;
            while (current_node != root) {
                path.push_back(current_node);
                current_node = parent[current_node];
            }
            path.push_back(root);

            std::string path_str;
            for (int i = path.size() - 1; i >= 0; --i) {
                path_str += path[i];
                if (i > 0) {
                    path_str += " -> ";
                }
            }
            return path_str;
        }

        const std::vector<char> neighbors = graph.getNeighbors(current_node);
        for (const auto& neighbor : neighbors) {
            std::pair<bool, double> edge_weight_wrapped = graph.getEdge(current_node, neighbor);
            // if it has an edge
            if (edge_weight_wrapped.first) {
                double edge_weight = edge_weight_wrapped.second;

                if (visited.find(neighbor) == visited.end()) {
                    double alt = dist[current_node] + edge_weight;

                    if (alt < dist[neighbor]) {
                        dist[neighbor] = alt;
                        parent[neighbor] = current_node;
                        queue.push({ alt, neighbor });
                    }
                }
            }
            // there is no edge between the two. it shouldn't get here
        }
    }

    std::cout << "Goal not reached" << std::endl;
    return "";
}
};