#include <graph/Graph.h>
#include <set>
#include <stack>
#include <unordered_map>

// https://en.wikipedia.org/wiki/Depth-first_search
// DFS(G, v)
//   label v as visited
//   if v is goal then return v
//   for all edges from v to w that are in G.adjacentEdges(v) do
//      if w is not labeled as explored then
//          recursively call DFS(G, w)
//
namespace DFS {

std::string traverse(const Graph<char>& graph, char root, char current_node, char goal, std::set<char>& visited, std::unordered_map<char, char>& parent)
{
    visited.insert(current_node);

    if (current_node == goal) {
        // we found the goal node so return the path
        std::vector<char> path;
        char node = goal;

        while (node != root) {
            path.push_back(node);
            node = parent[node];
        }

        path.push_back(root);

        std::string ret;
        for (int i = path.size() - 1; i >= 0; --i) {
            ret += path[i];
            if (i > 0) {
                ret += " -> ";
            }
        }

        return ret;
    }

    const std::vector<char> neighbors = graph.getNeighbors(current_node);
    for (const auto& neighbor : neighbors) {
        if (visited.find(neighbor) == visited.end()) {
            parent[neighbor] = current_node;
            std::string subpath = traverse(graph, root, neighbor, goal, visited, parent);
            if (!subpath.empty()) {
                return subpath;
            }
        }
    }

    return "";
}

std::string traverse(const Graph<char>& graph, char root, char goal)
{
    std::set<char> visited;
    std::unordered_map<char, char> parent;

    std::string ret = traverse(graph, root, root, goal, visited, parent);

    if (ret.empty()) {
        std::cout << "Goal not reached" << std::endl;
    }

    return ret;
}
}
