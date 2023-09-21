graph search algorithms
===

what it says on the tin


implemented algorithms:
- breadth-first search
- depth-first search
- basic queue dijkstra's algorithm
- bellman-ford


TODO:
- more


usage
---

```sh
./run.sh
# ...
#       A
#      /|\
#     B C D
#    / \ \  \
#   E   F G  H
#      /      \
#     I         J
#
# BFS(A,I): A -> B -> F -> I
# BFS(I,J): I -> F -> B -> A -> D -> H -> J
# DFS(B,J): B -> A -> D -> H -> J
# DFS(E,G): E -> B -> A -> C -> G
#
#        9
#     B --- E 
#  14/ \2    \6
#   / 9 \  11 \
#  A --- D --- F
#   \   /10   /
#   7\ /     /15
#     C ----
#
# Dijkstra(A,E): A -> D -> B -> E
#
#            ->:5, <-:-2
#     6/----> B <---> D
#     /       |  \ /-3^
#    A       8|   x   |7
#    ^\   7   v  / \-4|
#    | \----> C ----> E
#   2|            9  /
#    \--------------/
#
#
# BellmanFord(A,B): A -> C -> D -> B
```

the ascii representations kinda suck. the png's of the graphs are in `graphs`, using the `dumpGraph` functionality.

e.g.
```cpp
// ...
DijkstraGraph.dumpGraph("out.dot");
// ...
```

```sh
./viz.sh out.dot
```