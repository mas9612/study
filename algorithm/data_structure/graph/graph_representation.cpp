#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "Number of vertex: ";
    int num_of_vertex;
    cin >> num_of_vertex;

    vector<vector<int>> adj_list(num_of_vertex + 1);
    vector<vector<int>> adj_matrix(num_of_vertex + 1,
                                   vector<int>(num_of_vertex + 1, 0));
    for (int i = 1; i <= num_of_vertex; ++i) {
        cout << "Number of vertex of Node #" << i + 1 << "'s adjacency: ";
        int n;
        cin >> n;

        cout << "  Adjacencies (space separated): ";
        int tmp;
        for (int j = 0; j < n; ++j) {
            cin >> tmp;
            adj_list[i].push_back(tmp);
            adj_matrix[i][tmp] = 1;
        }
    }

    cout << "\nAdjacency list:\n";
    for (int i = 1; i <= num_of_vertex; ++i) {
        cout << setw(2) << i << ": ";
        int size = adj_list[i].size();
        if (size > 0) {
            cout << adj_list[i][0];
            for (int j = 1; j < size; ++j)
                cout << ' ' << adj_list[i][j];
            cout << '\n';
        }
    }

    cout << "\nAdjacency matrix:\n";
    cout << "   |";
    for (int i = 1; i <= num_of_vertex; ++i)
        cout << setw(2) << i;
    cout << "\n---";
    for (int i = 0; i <= num_of_vertex; ++i)
        cout << "--";
    cout << '\n';

    for (int i = 1; i <= num_of_vertex; ++i) {
        cout << setw(2) << i << " | ";
        cout << adj_matrix[i][1];
        for (int j = 2; j <= num_of_vertex; ++j)
            cout << ' ' << adj_matrix[i][j];
        cout << '\n';
    }
}
