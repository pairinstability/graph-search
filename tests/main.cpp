#include <BFS.h>
#include <graph/Graph.h>

int main()
{
    /*               A
     *              / \
     *             B   C
     *            /     \
     *           E ----- D 
    */
    Graph<char> BFSGraph(false);
    BFSGraph.addNode('A');
    BFSGraph.addNode('B');
    BFSGraph.addNode('C');
    BFSGraph.addNode('D');
    BFSGraph.addNode('E');
    BFSGraph.addEdge('A', 'B');
    BFSGraph.addEdge('A', 'C');
    BFSGraph.addEdge('C', 'D');
    BFSGraph.addEdge('B', 'E');
    BFSGraph.addEdge('E', 'D');

    std::cout << "BFS: ";
    BFS::traverse(BFSGraph, 'A', 'D');
    // BFS: A -> C -> D

    return 0;
}
