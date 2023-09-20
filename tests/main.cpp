#include <BFS.h>
#include <DFS.h>
#include <graph/Graph.h>

void runBFS(bool run)
{
    if (run) {
        /*               A
         *              /|\
         *             B C D
         *            / \ \  \
         *           E   F G  H
         *              /      \
         *             I         J
         */
        Graph<char> BFSGraph(false);
        BFSGraph.addNodes('A', 'B');
        BFSGraph.addNodes('A', 'C');
        BFSGraph.addNodes('A', 'D');
        BFSGraph.addNodes('B', 'E');
        BFSGraph.addNodes('B', 'F');
        BFSGraph.addNodes('C', 'G');
        BFSGraph.addNodes('D', 'H');
        BFSGraph.addNodes('F', 'I');
        BFSGraph.addNodes('J', 'H');

        std::cout << "BFS: ";
        BFS::traverse(BFSGraph, 'A', 'I');
        // BFS: A -> B -> F -> I
        std::cout << "BFS: ";
        BFS::traverse(BFSGraph, 'I', 'J');
        // BFS: I -> F -> B -> A -> D -> H -> J
    }
}

void runDFS(bool run)
{
    if (run) {
        /*               A
         *              /|\
         *             B C D
         *            / \ \  \
         *           E   F G  H
         *              /      \
         *             I         J
         */
        Graph<char> DFSGraph(false);
        DFSGraph.addNodes('A', 'B');
        DFSGraph.addNodes('A', 'C');
        DFSGraph.addNodes('A', 'D');
        DFSGraph.addNodes('B', 'E');
        DFSGraph.addNodes('B', 'F');
        DFSGraph.addNodes('C', 'G');
        DFSGraph.addNodes('D', 'H');
        DFSGraph.addNodes('F', 'I');
        DFSGraph.addNodes('H', 'J');

        std::cout << "DFS: ";
        DFS::traverse(DFSGraph, 'B', 'J');
        // DFS: B -> A -> D -> H -> J
        std::cout << "DFS: ";
        DFS::traverse(DFSGraph, 'E', 'G');
        // DFS: E -> B -> A -> C -> G
    }
}

int main()
{
    runBFS(true);
    runDFS(true);

    return 0;
}