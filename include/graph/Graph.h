#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>

template <typename T>
class Graph {
public:
    Graph(bool is_directed = false)
        : is_directed(is_directed)
    {
    }

    void addNode(const T& node)
    {
        if (nodes.find(node) == nodes.end()) {
            nodes[node] = std::vector<T>();
        }
    }

    void addEdge(const T& from, const T& to)
    {
        if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end()) {
            std::cerr << "Node not found" << std::endl;
            return;
        }

        nodes[from].push_back(to);
        if (!is_directed) {
            nodes[to].push_back(from);
        }
    }

    std::vector<T> getNeighbors(char node) const
    {
        if (nodes.find(node) != nodes.end()) {
            return nodes.at(node);
        } else {
            return std::vector<char>();
        }
    }

    void printGraph() const
    {
        for (const auto& entry : nodes) {
            const T& node = entry.first;
            const std::vector<T>& neighbors = entry.second;

            for (const T& neighbor : neighbors) {
                if (is_directed) {
                    // Print as directed edge
                    std::cout << node << " -> " << neighbor << std::endl;
                } else {
                    // Print as undirected edge
                    std::cout << node << " - " << neighbor << std::endl;
                }
            }
        }
    }

private:
    /* the nodes are represented as a unique key : list of adjacent nodes */
    std::unordered_map<T, std::vector<T>> nodes;
    bool is_directed;
};

#endif // GRAPH_H