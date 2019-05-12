#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Node {
   public:
    vector<int> adjacencies;
    vector<int> costs;

    int cost;
    bool fixed;
};

void prepare_graph(vector<Node>& G) {
    Node n1, n2, n3, n4, n5, n6;

    n1.adjacencies.push_back(2);
    n1.adjacencies.push_back(3);
    n1.adjacencies.push_back(4);
    n1.costs.push_back(5);
    n1.costs.push_back(4);
    n1.costs.push_back(2);

    n2.adjacencies.push_back(1);
    n2.adjacencies.push_back(3);
    n2.adjacencies.push_back(5);
    n2.costs.push_back(5);
    n2.costs.push_back(2);
    n2.costs.push_back(6);

    n3.adjacencies.push_back(1);
    n3.adjacencies.push_back(2);
    n3.adjacencies.push_back(4);
    n3.adjacencies.push_back(6);
    n3.costs.push_back(4);
    n3.costs.push_back(2);
    n3.costs.push_back(3);
    n3.costs.push_back(2);

    n4.adjacencies.push_back(1);
    n4.adjacencies.push_back(3);
    n4.adjacencies.push_back(6);
    n4.costs.push_back(2);
    n4.costs.push_back(3);
    n4.costs.push_back(6);

    n5.adjacencies.push_back(2);
    n5.adjacencies.push_back(6);
    n5.costs.push_back(6);
    n5.costs.push_back(4);

    n6.adjacencies.push_back(3);
    n6.adjacencies.push_back(4);
    n6.adjacencies.push_back(5);
    n6.costs.push_back(2);
    n6.costs.push_back(6);
    n6.costs.push_back(4);

    Node dummy;
    G.push_back(dummy);  // adjust for 1-origin
    G.push_back(n1);
    G.push_back(n2);
    G.push_back(n3);
    G.push_back(n4);
    G.push_back(n5);
    G.push_back(n6);
}

void print_graph_info(vector<Node>& G) {
    for (int i = 1; i < G.size(); ++i) {
        cout << "Node #" << i << '\n';
        for (int j = 0; j < G[i].adjacencies.size(); ++j)
            cout << "  Edge #" << j + 1 << " is connected to Node #"
                 << G[i].adjacencies[j] << " (cost " << G[i].costs[j] << ")\n";
    }
}

int dijkstra(vector<Node>& G, int start, int goal) {
    // initialize cost
    for (int i = 1; i < G.size(); ++i) {
        G[i].cost = INT_MAX;
        G[i].fixed = false;
    }
    G[start].cost = 0;
    G[start].fixed = true;

    for (int i = 0; i < G[start].adjacencies.size(); ++i) {
        int node = G[start].adjacencies[i];
        G[node].cost = G[start].costs[i];
    }

    while (true) {
        int current = -1;
        int cost = INT_MAX;
        for (int i = 1; i < G.size(); ++i) {
            if (!G[i].fixed && cost > G[i].cost) {
                current = i;
                cost = G[i].cost;
            }
        }
        if (current == -1)  // all nodes fixed
            break;
        G[current].fixed = true;

        for (int i = 0; i < G[current].adjacencies.size(); ++i) {
            int adjacency = G[current].adjacencies[i];
            int via_current = cost + G[current].costs[i];
            if (!G[adjacency].fixed && via_current < G[adjacency].cost)
                G[adjacency].cost = via_current;
        }
    }

    for (int i = 1; i < G.size(); ++i) {
        cout << "Cost of Node #" << start << " to #" << i << " is " << G[i].cost
             << '\n';
    }

    return G[goal].cost;
}

int main() {
    vector<Node> G;
    prepare_graph(G);

    int cost = dijkstra(G, 1, 5);
    cout << "Minimum cost from Node #1 to Node #5 is " << cost << '\n';
}
