#ifndef GRAPH_H
#define GRAPH_H

#include <cassert>
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
        // if node doesn't exist then add. else we do nothing
        if (nodes.find(node) == nodes.end()) {
            nodes[node] = std::vector<T>();
            Debug::print("addNode: Added node: ", node);
        }
    }

    // add weighted edge
    void addEdge(const T& from, const T& to, double weight)
    {
        // if any of the nodes specified don't exist then we can't add an edge
        // between them
        if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end()) {
            Debug::print("addEdge: One of the nodes specified, either ", from, " or ", to, " in addEdge does not exist");
            return;
        }

        // add adjacent nodes
        nodes[from].emplace_back(to);
        // add edge relationship and weight
        edges.emplace_back(from, to, weight);

        if (!is_directed) {
            // if its undirected then we need to implicitly add the relationship between nodes
            // as its bidirectional
            // if the graph is directed, the relationship from->to is explicitly set
            nodes[to].emplace_back(from);
        }

        if (!is_directed && !is_weighted) {
            Debug::print("addEdge: Added nodes: ", from, "-", to);
        } else if (!is_directed) {
            Debug::print("addEdge: Added nodes: ", from, "-", weight, "-", to);
        } else if (is_directed && !is_weighted) {
            Debug::print("addEdge: Added nodes: ", from, "->", to);
        } else {
            Debug::print("addEdge: Added nodes: ", from, "-", weight, ">", to);
        }
    }

    // add non-weighted edge (actually weighted with unity)
    void addEdge(const T& from, const T& to)
    {
        addEdge(from, to, 1.0);
    }

    std::vector<T> getNeighbors(const T& node) const
    {
        if (nodes.find(node) != nodes.end()) {
            Debug::print("getNeighbors: Found node ", node, " and returning adjacents");
            return nodes.at(node);
        } else {
            Debug::print("getNeighbors: No adjacents found for node ", node);
            return std::vector<T>();
        }
    }

    // find and return the weight between two nodes. if it doesn't exist then
    // the bool is false and the weight is 0.
    std::pair<bool, double> getEdge(const T& from, const T& to) const
    {
        for (const auto& edge : edges) {
            T from_internal = std::get<0>(edge);
            T to_internal = std::get<1>(edge);
            double weight = std::get<2>(edge);

            // loop through the edges and find the corresponding edge
            // if the graph is directed then we treat from,to as distinct from to,from
            // but if its undirected then we treat it as the same
            if ((from_internal == from && to_internal == to) || (!is_directed && from_internal == to && to_internal == from)) {
                return std::make_pair(true, weight);
            }
        }
        // no edge found
        return std::make_pair(false, 0.0);
    }

    double getNumNodes()
    {
        return nodes.size();
    }

    double getNumEdges()
    {
        return edges.size();
    }

    bool getIsDirected() const
    {
        return is_directed;
    }

    bool getIsWeighted() const
    {
        return is_weighted;
    }

    // returns all the nodes only, not their adjacents
    std::vector<T> getNodes() const
    {
        std::vector<T> all_nodes;
        for (const auto& entry : nodes) {
            all_nodes.push_back(entry.first);
        }
        return all_nodes;
    }

    // dump the graph in dot format to a file
    void dumpGraph(const std::string& filename) const
    {
        Debug::print("Dumping graph");
        std::ofstream outfile(filename);

        if (!outfile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        outfile << (is_directed ? "digraph" : "graph") << " G {" << std::endl;
        outfile << "  splines=false" << std::endl;

        for (const auto& edge : edges) {
            T from = std::get<0>(edge);
            T to = std::get<1>(edge);
            double weight = std::get<2>(edge);

            outfile << "  " << from << " ";
            if (is_directed) {
                outfile << "->";
            } else {
                outfile << "--";
            }
            outfile << " " << to;

            // adding attributes
            outfile << " [";
            if (!is_directed) {
                outfile << "dir=none ";
            }

            if (is_weighted) {
                outfile << "label=" << weight;
            }

            outfile << "];" << std::endl;
        }

        outfile << "}" << std::endl;
        outfile.close();
    }

private:
    // nodes are stored as node, adjacent nodes
    std::unordered_map<T, std::vector<T>> nodes;
    // edges are stored as from, to, weight. in unweighted graphs, the weight
    // is just unity (1) so its treated as meaningless in that context
    std::vector<std::tuple<T, T, double>> edges;

    bool is_directed;
    bool is_weighted;
};

#endif // GRAPH_H