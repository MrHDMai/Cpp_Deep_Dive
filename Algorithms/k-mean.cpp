#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

using Point = pair<double, double>;

double euclideanDistance(const Point& a, const Point& b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

Point computeCentroid(const vector<Point>& cluster) {
    double sumX = 0, sumY = 0;
    for (const auto& p : cluster) {
        sumX += p.first;
        sumY += p.second;
    }
    int size = cluster.size();
    return { sumX / size, sumY / size };
}

void kmeans(vector<Point>& points, int k, int maxIter = 100) {
    int n = points.size();
    vector<Point> centroids;
    vector<int> labels(n, -1);

    srand(time(0));
    // Step 1: Initialize centroids randomly
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points[rand() % n]);
    }

    for (int iter = 0; iter < maxIter; ++iter) {
        bool changed = false;

        // Step 2: Assign each point to the closest centroid
        for (int i = 0; i < n; ++i) {
            double minDist = numeric_limits<double>::max();
            int bestCluster = -1;
            for (int j = 0; j < k; ++j) {
                double dist = euclideanDistance(points[i], centroids[j]);
                if (dist < minDist) {
                    minDist = dist;
                    bestCluster = j;
                }
            }
            if (labels[i] != bestCluster) {
                changed = true;
                labels[i] = bestCluster;
            }
        }

        if (!changed) break; // Clusters are stable

        // Step 3: Recalculate centroids
        vector<vector<Point>> clusters(k);
        for (int i = 0; i < n; ++i) {
            clusters[labels[i]].push_back(points[i]);
        }

        for (int j = 0; j < k; ++j) {
            if (!clusters[j].empty()) {
                centroids[j] = computeCentroid(clusters[j]);
            }
        }
    }

    // Output final clusters
    cout << "\nFinal Clusters:\n";
    for (int i = 0; i < k; ++i) {
        cout << "Cluster " << i << ": ";
        for (int j = 0; j < n; ++j) {
            if (labels[j] == i)
                cout << "(" << points[j].first << "," << points[j].second << ") ";
        }
        cout << endl;
    }
}

int main() {
    vector<Point> data = {
        {1.0, 2.0}, {1.5, 1.8}, {5.0, 8.0},
        {8.0, 8.0}, {1.0, 0.6}, {9.0, 11.0},
        {8.0, 2.0}, {10.0, 2.0}, {9.0, 3.0}
    };

    int k = 3;
    kmeans(data, k);

    return 0;
}
