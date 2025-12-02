#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max() / 2; // Avoid overflow on addition

void floydWarshall(vector<vector<int>>& dist) {
    int V = dist.size();

    for (int k = 0; k < V; ++k) {           // intermediate vertex
        for (int i = 0; i < V; ++i) {       // source vertex
            for (int j = 0; j < V; ++j) {   // destination vertex
                if (dist[i][k] < INF && dist[k][j] < INF)  // avoid overflow
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

void printMatrix(const vector<vector<int>>& dist) {
    int V = dist.size();
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << dist[i][j];
        }
        cout << "\n";
    }
}

int main() {
    int V = 4;
    vector<vector<int>> graph = {
        {0,   3,   INF,  7},
        {8,   0,   2,    INF},
        {5,   INF, 0,    1},
        {2,   INF, INF,  0}
    };

    cout << "Initial Graph (Adjacency Matrix):\n";
    printMatrix(graph);

    floydWarshall(graph);

    cout << "\nShortest Distances Between Every Pair:\n";
    printMatrix(graph);
}
