#include <graph/Graph.h>
#include <queue>
#include <set>
#include <unordered_map>

// https://en.wikipedia.org/wiki/Breadth-first_search
//
// BFS(G, root, goal)
//  let Q be a queue
//  Q.enqueue(root)
//  label root as explored
//  while Q is not empty do
//      v := Q.dequeue()
//      if v is goal then return v
//      for all edges from v to w in G.adjacentEdges(v) do
//          if w is not labeled as explored then
//              label w as explored
//              w.parent := v
//              Q.enqueue(w)
//
namespace BFS {
std::string traverse(const Graph<char>& graph, char root, char goal)
{
    std::queue<char> queue;
    std::set<char> visited;
    std::unordered_map<char, char> parent;

    queue.push(root);
    visited.insert(root);

    while (!queue.empty()) {
        char current_node = queue.front();
        queue.pop();

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

        const std::vector<std::pair<char, double>>& neighbors = graph.getNeighbors(current_node);
        for (const auto& neighbor_pair : neighbors) {
            char neighbor = neighbor_pair.first;
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current_node;
                queue.push(neighbor);
            }
        }
    }

    std::cout << "Goal not reached" << std::endl;
    return "";
}
}