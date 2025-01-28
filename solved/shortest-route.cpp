#include <iostream>
#include <vector>
#include <array>
#include <queue>

using i64 = long long;

// dijkstra
class Solution {
public:
    using T = std::array<i64, 2>;

    const int n;
    const i64 INF;
    std::vector<i64> dist;
    std::vector<std::vector<T>> adj;

    Solution(int nodes) : n(nodes), INF(1e18) {
        dist = std::vector<i64>(n, INF);
        adj = std::vector<std::vector<T>>(n);
    }

    void dijkstra(int source) {
        std::priority_queue<T, std::vector<T>, std::greater<T>> pq;
        pq.push({0, source});
        dist[source] = 0;

        while (!pq.empty()) {
            T curr = pq.top();
            i64 cost = curr[0];
            int u = curr[1]; 
            pq.pop();

            if (dist[u] < cost) continue;

            for (T next : adj[u]) {
                i64 cost_v = next[0];
                int v = next[1]; 
                if (cost_v + cost < dist[v]) {
                    dist[v] = cost_v + cost;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    void add_edge(int a, int b, int cost) {
        adj[a].push_back({cost, b});
    }

    void dists() {
        for (i64 x : dist) std::cout << x << ' ';
        std::cout << "\n";
    }

};

int main() {
    int n, m;
    std::cin >> n >> m;
    Solution sol = Solution(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        --a, --b;

        sol.add_edge(a, b, c);
    }
    sol.dijkstra(0);
    sol.dists();
}
