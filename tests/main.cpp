#include <BFS.h>
#include <DFS.h>
#include <Dijkstra.h>
#include <BellmanFord.h>
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
        std::cout << "BFS(A,I): A -> B -> F -> I" << std::endl;

        // BFS: I -> F -> B -> A -> D -> H -> J
        assert(BFS::traverse(BFSGraph, 'I', 'J') == "I -> F -> B -> A -> D -> H -> J");
        std::cout << "BFS(I,J): I -> F -> B -> A -> D -> H -> J" << std::endl;
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
        std::cout << "DFS(B,J): B -> A -> D -> H -> J" << std::endl;

        assert(DFS::traverse(DFSGraph, 'E', 'G') == "E -> B -> A -> C -> G");
        std::cout << "DFS(E,G): E -> B -> A -> C -> G" << std::endl;
    }
}

// Dijkstra, basic queue
void runDijkstra(bool run)
{
    if (run) {
        /*              9
         *           B --- E
         *        14/ \2    \6
         *         / 9 \  11 \
         *        A --- D --- F
         *         \   /10   /
         *         7\ /     /15
         *           C ----
         */
        Graph<char> DijkstraGraph(false, true);
        DijkstraGraph.addNodes('A', 'C', 7.0);
        DijkstraGraph.addNodes('A', 'B', 14.0);
        DijkstraGraph.addNodes('A', 'D', 9.0);
        DijkstraGraph.addNodes('C', 'F', 15.0);
        DijkstraGraph.addNodes('C', 'D', 10.0);
        DijkstraGraph.addNodes('D', 'B', 2.0);
        DijkstraGraph.addNodes('B', 'E', 9.0);
        DijkstraGraph.addNodes('E', 'F', 6.0);
        DijkstraGraph.addNodes('D', 'F', 11.0);

        assert(Dijkstra::traverse(DijkstraGraph, 'A', 'E') == "A -> D -> B -> E");
        std::cout << "Dijkstra(A,E): A -> D -> B -> E" << std::endl;
    }
}

// Bellman-Ford
void runBellmanFord(bool run) {
    if (run) {
        /*            ->:5, <-:-2
         *     6/----> B <---> D
         *     /       |  \ /-3^
         *    A       8|   x   |7
         *    ^\   7   v  / \-4|
         *    | \----> C ----> E
         *   2|            9  /
         *    \--------------/
         */

        Graph<char> BellmanfordGraph(true, true);
        BellmanfordGraph.addNodes('A', 'B', 6.0);
        BellmanfordGraph.addNodes('A', 'C', 7.0);
        BellmanfordGraph.addNodes('B', 'C', 8.0);
        BellmanfordGraph.addNodes('B', 'D', 5.0);
        BellmanfordGraph.addNodes('D', 'B', -2.0);
        BellmanfordGraph.addNodes('C', 'E', 9.0);
        BellmanfordGraph.addNodes('E', 'A', 2.0);
        BellmanfordGraph.addNodes('E', 'D', 7.0);
        BellmanfordGraph.addNodes('B', 'E', -4.0);
        BellmanfordGraph.addNodes('C', 'D', -3.0);

        assert(BellmanFord::traverse(BellmanfordGraph, 'A', 'B') == "A -> C -> D -> B");
        std::cout << "BellmanFord(A,B): A -> C -> D -> B" << std::endl;
    }
}

int main()
{
    runBFS(true);
    runDFS(true);
    runDijkstra(true);
    runBellmanFord(true);

    return 0;
}