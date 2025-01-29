#include <bits/stdc++.h>
 
using i64 = long long;

class Solution {
    const int n;
    std::vector<bool> vis;
    std::vector<std::vector<std::pair<int, int>>> adj;
    std::vector<int> dist;

public:
    Solution(int nodes) : n(nodes) {
        adj = std::vector<std::vector<std::pair<int, int>>>(n + 1);
        dist = std::vector<int>(n + 1, 0);
    }

    void bellman_ford() {
        for (int i = 0; i < n - 1; i++) {
            for (int u = 0; u < n; u++) {
                if (dist[u] == INT32_MAX) {
                    continue;
                }

                for (auto &[v, cost] : adj[u]) {
                    dist[v] = std::min(dist[v], dist[u] + cost);
                }
            }
        }

        std::queue<int> Q;
        for (int u = 0; u < n; u++) {
            if (dist[u] == INT32_MAX) {
                continue;
            }

            for (auto &[v, cost] : adj[u]) {
                // clcyles nodes
                if (dist[u] + cost < dist[v]) {
                    Q.push(v);
                }
            }
        }
        
        std::vector<bool> is_negative(n, false);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            is_negative[u] = true;
            for (auto &[v, cost] : adj[u]) {
                if (is_negative[v]) {
                    continue;
                }
                Q.push(v);
            }
       }
        
       // nr targets
       int q = 5;
       for (int i = 0; i < q; i++) {
           int target;
           std::cin >> target;

           if (is_negative[target]) {
               std::cout << "-Infinity" << '\n';
           } else if (dist[target] == INT32_MAX) {
               std::cout << "Impossible" << '\n';
           } else {
               std::cout << dist[target] << '\n';
           }
       }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // not_tested
}
