#include <iostream>
#include <vector>
#include <limits>
#include <memory>
using namespace std;

struct Edge {
    int u, v, weight;
};

// Abstract base class for graph representations
class Graph {
public:
    virtual ~Graph() = default;
    virtual vector<Edge> getEdges() const = 0;
    virtual int getNumNodes() const = 0;
};

// Concrete graph implementation using edge list
class EdgeListGraph : public Graph {
    vector<Edge> edges;
    int numNodes;
    
public:
    EdgeListGraph(int nodes, const vector<Edge>& edges) 
        : numNodes(nodes), edges(edges) {}

    vector<Edge> getEdges() const override {
        return edges;
    }

    int getNumNodes() const override {
        return numNodes;
    }
};

// Bellman-Ford algorithm implementation
class BellmanFord {
    unique_ptr<const Graph> graph;
    int source;
    vector<long long> distances;
    bool hasNegativeCycle;

public:
    BellmanFord(unique_ptr<const Graph> g, int src) 
        : graph(move(g)), source(src), hasNegativeCycle(false) {}

    void run() {
        const int numNodes = graph->getNumNodes();
        const auto& edges = graph->getEdges();
        
        distances.resize(numNodes, numeric_limits<long long>::max());
        distances[source] = 0;

        bool updated;
        for (int i = 0; i < numNodes - 1; ++i) {
            updated = false;
            for (const auto& edge : edges) {
                if (distances[edge.u] != numeric_limits<long long>::max() &&
                    distances[edge.u] + edge.weight < distances[edge.v]) {
                    distances[edge.v] = distances[edge.u] + edge.weight;
                    updated = true;
                }
            }
            if (!updated) break;
        }

        // Check for negative cycles
        for (const auto& edge : edges) {
            if (distances[edge.u] != numeric_limits<long long>::max() &&
                distances[edge.v] > distances[edge.u] + edge.weight) {
                hasNegativeCycle = true;
                return;
            }
        }
        hasNegativeCycle = false;
    }

    void printResults() const {
        if (hasNegativeCycle) {
            cout << "Graph contains a negative weight cycle!\n";
            return;
        }

        cout << "Shortest distances from source " << source << ":\n";
        for (size_t i = 0; i < distances.size(); ++i) {
            if (distances[i] == numeric_limits<long long>::max()) {
                cout << "Node " << i << ": unreachable\n";
            } else {
                cout << "Node " << i << ": " << distances[i] << "\n";
            }
        }
    }

    bool containsNegativeCycle() const { return hasNegativeCycle; }
    const vector<long long>& getDistances() const { return distances; }
};

int main() {
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 5}, {2, 1, -3}, {1, 3, 1}
    };

    unique_ptr<Graph> graph = make_unique<EdgeListGraph>(4, edges);
    BellmanFord bf(move(graph), 0);
    bf.run();
    bf.printResults();

    return 0;
}