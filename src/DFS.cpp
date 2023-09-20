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
void traverse(const Graph<char>& graph, char root, char current_node, char goal, std::set<char>& visited, std::unordered_map<char, char>& parent)
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


        for (int i = path.size() - 1; i >= 0; --i) {
            std::cout << path[i];
            if (i > 0) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;

        return;
    }

    const std::vector<char>& neighbors = graph.getNeighbors(current_node);
    for (char neighbor : neighbors) {
        if (visited.find(neighbor) == visited.end()) {
            parent[neighbor] = current_node;
            traverse(graph, root, neighbor, goal, visited, parent);
        }
    }

}

void traverse(const Graph<char>& graph, char root, char goal)
{
    std::set<char> visited;
    std::unordered_map<char, char> parent;

    traverse(graph, root, root, goal, visited, parent);

    if (visited.find(goal) == visited.end()) {
        std::cout << "Goal not reached" << std::endl;
    }
}
}
