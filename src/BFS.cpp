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
void traverse(const Graph<char>& graph, char root, char goal)
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
                visited.insert(neighbor);
                parent[neighbor] = current_node;
                queue.push(neighbor);
            }
        }
    }

    std::cout << "Goal not reached" << std::endl;
    return;
}
}