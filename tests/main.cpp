#include <BFS.h>
#include <DFS.h>
#include <cassert>
#include <graph/Graph.h>

// unweighted, undirected breadth-first
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

        // BFS: A -> B -> F -> I
        assert(BFS::traverse(BFSGraph, 'A', 'I') == "A -> B -> F -> I");
        std::cout << "BFS: A -> B -> F -> I" << std::endl;

        // BFS: I -> F -> B -> A -> D -> H -> J
        assert(BFS::traverse(BFSGraph, 'I', 'J') == "I -> F -> B -> A -> D -> H -> J");
        std::cout << "BFS: I -> F -> B -> A -> D -> H -> J" << std::endl;
    }
}

// unweighted, undirected depth-first
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

        assert(DFS::traverse(DFSGraph, 'B', 'J') == "B -> A -> D -> H -> J");
        std::cout << "DFS: B -> A -> D -> H -> J" << std::endl;

        assert(DFS::traverse(DFSGraph, 'E', 'G') == "E -> B -> A -> C -> G");
        std::cout << "DFS: E -> B -> A -> C -> G" << std::endl;

        DFSGraph.dumpGraph("out.dot");
    }
}

int main()
{
    runBFS(true);
    runDFS(true);

    return 0;
}