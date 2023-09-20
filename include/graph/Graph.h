#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utils/Debug.h>
#include <vector>

template <typename T>
class Graph {
public:
    Graph(bool is_directed = false, bool is_weighted = false)
        : is_directed(is_directed)
        , is_weighted(is_weighted)
    {
    }

    // add nodes with weighted edge
    void addNodes(const T& from, const T& to, double weight)
    {
        addNode(from);
        addNode(to);
        addEdge(from, to, weight);
    }

    // add node without weighted edge (default unity edge)
    void addNodes(const T& from, const T& to)
    {
        addNodes(from, to, 1.0);
    }

    // add only a node
    void addNode(const T& node)
    {
        if (nodes.find(node) == nodes.end()) {
            nodes[node] = std::vector<std::pair<T, double>>();
        }
        Debug::print("Added node: ", node);
    }

    // add weighted edge
    void addEdge(const T& from, const T& to, double weight)
    {
        if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end()) {
            return;
        }

        // weights are added to dominating nodes, like for the case
        // A -> B, A has the weight assigned. technically B has a weight
        // but its unused and has no actual purpose, unless it is also dominating
        // like if A -> B -> C
        nodes[from].emplace_back(to, weight);
        if (!is_directed) {
            // as undirected graphs have bilateral relationships, we add the from node here
            // but both weights don't really mean anything for unweighted graphs
            nodes[to].emplace_back(from, weight);
        }

        if (!is_directed && !is_weighted) {
            Debug::print("Added nodes: ", from, "-", to);
        } else if (!is_directed) {
            Debug::print("Added nodes: ", from, "-", weight, "-", to);
        } else if (is_directed && !is_weighted) {
            Debug::print("Added nodes: ", from, "->", to);
        } else {
            Debug::print("Added nodes: ", from, "-", weight, ">", to);
        }
    }

    // add non-weighted edge (actually weighted with unity)
    void addEdge(const T& from, const T& to)
    {
        addEdge(from, to, 1.0);
    }

    std::vector<std::pair<T, double>> getNeighbors(const T& node) const
    {
        if (nodes.find(node) != nodes.end()) {
            return nodes.at(node);
        } else {
            return std::vector<std::pair<T, double>>();
        }
    }

    // dump the graph in dot format to a file
    void dumpGraph(const std::string& filename) const
    {
        std::ofstream outfile(filename);

        if (!outfile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        outfile << (is_directed ? "digraph" : "graph") << " G {" << std::endl;

        for (const auto& entry : nodes) {
            const T& node = entry.first;
            const std::vector<std::pair<T, double>>& neighbors = entry.second;

            for (const auto& neighbor_pair : neighbors) {
                T neighbor = neighbor_pair.first;
                double weight = neighbor_pair.second;

                if (is_directed || node < neighbor) {
                    outfile << "  " << node << " ";
                    if (is_directed) {
                        outfile << "->";
                    } else {
                        outfile << "--";
                    }
                    outfile << " " << neighbor;

                    // if the graph is weighted, include the weight in the edge
                    if (is_weighted) {
                        outfile << " [label=" << weight << "]";
                    }

                    outfile << ";" << std::endl;
                }
            }
        }

        outfile << "}" << std::endl;
        outfile.close();
    }

    double getSize()
    {
        return nodes.size();
    }

    bool getIsDirected() const {
        return is_directed;
    }

    bool getIsWeighted() const {
        return is_weighted;
    }

private:
    // the graph consists of nodes, connected with weighted edges. even in unweighted
    // graphs, there are technically weights but they are unity (1). nodes
    // are represented as a unique key : list of adjacent nodes. each node
    // comprises this key and a weight
    // the nodes are represented as a unique key : list of adjacent nodes
    std::unordered_map<T, std::vector<std::pair<T, double>>> nodes;
    bool is_directed;
    bool is_weighted;
};

#endif // GRAPH_H