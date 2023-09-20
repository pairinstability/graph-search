#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <utils/Debug.h>
#include <vector>

template <typename T>
class Graph {
public:
    Graph(bool is_directed = false)
        : is_directed(is_directed)
    {
    }

    // add a from and to node and create the edge
    void addNodes(const T& from, const T& to)
    {
        // check if the nodes exist. if not, add them
        if (nodes.find(from) == nodes.end()) {
            nodes[from] = std::vector<T>();
        }

        if (nodes.find(to) == nodes.end()) {
            nodes[to] = std::vector<T>();
        }

        // add the edge between the two
        nodes[from].push_back(to);
        if (!is_directed) {
            nodes[to].push_back(from);
        }

        if (!is_directed) {
            Debug::print("Added nodes: ", from, "-", to);
        } else {
            Debug::print("Added nodes: ", from, "->", to);
        }
    }

    // add only a node
    void addNode(const T& node)
    {
        if (nodes.find(node) == nodes.end()) {
            nodes[node] = std::vector<T>();
        }
        Debug::print("Added node: ", node);
    }

    // add only an edge
    void addEdge(const T& from, const T& to)
    {
        if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end()) {
            return;
        }

        nodes[from].push_back(to);
        if (!is_directed) {
            nodes[to].push_back(from);
        }

        if (!is_directed) {
            Debug::print("Added undirected edge for: ", from, "-", to);
        } else {
            Debug::print("Added directed edge for: ", from, "->", to);
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

    // TOD: this kinda sucks. need to make this easier to read
    void printGraph() const
    {
        for (const auto& entry : nodes) {
            const T& node = entry.first;
            const std::vector<T>& neighbors = entry.second;

            for (const T& neighbor : neighbors) {
                if (is_directed) {
                    std::cout << node << " -> " << neighbor << std::endl;
                } else {
                    std::cout << node << " - " << neighbor << std::endl;
                }
            }
        }
    }

    double getSize()
    {
        return nodes.size();
    }

private:
    // the nodes are represented as a unique key : list of adjacent nodes
    std::unordered_map<T, std::vector<T>> nodes;
    bool is_directed;
};

#endif // GRAPH_H