#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18; // Large value representing infinity

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    // Initialize dist matrix: 1-indexed for convenience
    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));

    // Distance from a node to itself is 0
    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0;
    }

    // Read all M gateways
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        // In case of multiple edges between same pair, keep the minimum weight
        if (w < dist[u][v]) {
            dist[u][v] = w;
            dist[v][u] = w;
        }
    }

    // Floyd-Warshall Algorithm: O(N^3)
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Process Q queries: O(1) per query
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        if (dist[a][b] >= INF) {
            cout << -1 << "\n";
        } else {
            cout << dist[a][b] << "\n";
        }
    }

    return 0;
}
