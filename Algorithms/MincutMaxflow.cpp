struct MCMF {
    static const long long INF = 1e18;

    struct Edge {
        int to, rev;
        long long cap, cost;
    };

    int N;
    vector<vector<Edge>> G;
    vector<long long> dist, potential;
    vector<int> parent_v, parent_e;

    MCMF(int n) : N(n), G(n), dist(n), potential(n),
                  parent_v(n), parent_e(n) {}

    void addEdge(int u, int v, long long cap, long long cost) {
        Edge a = {v, (int)G[v].size(), cap, cost};
        Edge b = {u, (int)G[u].size(), 0, -cost};
        G[u].push_back(a);
        G[v].push_back(b);
    }

    // Returns (flow, cost)
    pair<long long,long long> min_cost_max_flow(int s, int t) {
        long long flow = 0, cost = 0;

        // Initialize potentials with Bellman-Ford (optional)
        fill(potential.begin(), potential.end(), 0);

        while (true) {
            // Dijkstra
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;

            priority_queue<pair<long long,int>,
                           vector<pair<long long,int>>,
                           greater<pair<long long,int>>> pq;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d != dist[u]) continue;

                for (int i = 0; i < (int)G[u].size(); i++) {
                    Edge &e = G[u][i];
                    if (e.cap > 0) {
                        long long nd = d + e.cost + potential[u] - potential[e.to];
                        if (nd < dist[e.to]) {
                            dist[e.to] = nd;
                            parent_v[e.to] = u;
                            parent_e[e.to] = i;
                            pq.push({nd, e.to});
                        }
                    }
                }
            }

            if (dist[t] == INF)
                break; // No more augmenting path

            // Update potentials
            for (int i = 0; i < N; i++)
                if (dist[i] < INF)
                    potential[i] += dist[i];

            // Determine max flow on path
            long long push = INF;
            for (int v = t; v != s; v = parent_v[v]) {
                Edge &e = G[parent_v[v]][parent_e[v]];
                push = min(push, e.cap);
            }

            // Apply flow
            for (int v = t; v != s; v = parent_v[v]) {
                Edge &e = G[parent_v[v]][parent_e[v]];
                e.cap -= push;
                G[v][e.rev].cap += push;
            }

            flow += push;
            cost += push * potential[t];
        }

        return {flow, cost};
    }
};
