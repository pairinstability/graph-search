graph search algorithms
===

what it says on the tin


implemented algorithms:
- breadth-first search
- depth-first search
- basic queue dijkstra's algorithm



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
```

there is a `dumpGraph` method in the `Graph` class that dumps the graph into a graphviz dot format, upon which the `viz.sh` script can be used to compile and convert it to a png.

e.g.
```cpp
// ...
DijkstraGraph.dumpGraph("out.dot");
// ...
```

```sh
./viz.sh out.dot
```