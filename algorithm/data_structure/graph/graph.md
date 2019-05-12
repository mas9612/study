# Graph

## Terms
![](image/graph.png)

* Vertex: each point (node) in graph
* Edge: component to connect two vertices

Graphs are divided into two categories, connected graph and disconnected graph.

### Connected Graph
![](image/connected-graph-example.png)

* All vertices are connected.
    - if you pick any combination of two vertices, they are connected with edges.

### Disconnected Graph
![](image/disconnected-graph-example.png)

* Some vertices are disconnected.
    - Some combination of two vertices is not connected with edges and cannot reach from one vertex to another one.

## Graph representation in computer
* Adjacency list
    - array of each element (that is represent one node) has the array which is the set of its adjacency vertex (connected with only one edge)
        - e.g.) if vertex 1 is connected with vertex 4 and 6, `G[1]` is the array which has `4` and `6`.
* Adjacency matrix
    - two-dimensional array which represents edges
        - e.g.) if vertex 1 and 2 is connected, `G[1][2]` is `1`. Otherwise `0`.
