#include <graph/Graph.h>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace BellmanFord {
std::string traverse(const Graph<char>& graph, char root, char goal)
{
    std::unordered_map<char, double> dist;
    std::unordered_map<char, char> parent;
    std::vector<char> nodes = graph.getNodes();

    for (const auto& entry : nodes) {
        dist[entry] = std::numeric_limits<double>::infinity();
        parent[entry] = 0;
    }

    dist[root] = 0.0;

    // relax edges
    for (int i = 0; i < nodes.size() - 1; ++i) {
        for (const auto& node : nodes) {
            const std::vector<char> neighbors = graph.getNeighbors(node);
            for (const auto& neighbor : neighbors) {
                std::pair<bool, double> edge_weight_wrapped = graph.getEdge(node, neighbor);
                if (edge_weight_wrapped.first) {
                    double edge_weight = edge_weight_wrapped.second;

                    if (dist[node] + edge_weight < dist[neighbor]) {
                        dist[neighbor] = dist[node] + edge_weight;
                        parent[neighbor] = node;
                    }
                }
            }
        }
    }

    // check for negative weight cycles
    for (const auto& node : nodes) {
        const std::vector<char> neighbors = graph.getNeighbors(node);
        for (const auto& neighbor : neighbors) {
            std::pair<bool, double> edge_weight_wrapped = graph.getEdge(node, neighbor);
            if (edge_weight_wrapped.first) {
                double edge_weight = edge_weight_wrapped.second;

                if (dist[node] + edge_weight < dist[neighbor]) {
                    std::cout << "Negative weight cycle detected" << std::endl;
                    return "";
                }
            }
        }
    }

    if (dist[goal] != std::numeric_limits<double>::infinity()) {
        std::vector<char> path;

        char current_node = goal;
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

    std::cout << "Goal not reached" << std::endl;
    return "";
}
};
