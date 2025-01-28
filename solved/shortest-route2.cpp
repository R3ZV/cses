#include <iostream>
#include <vector>
#include <array>
#include <queue>

using i64 = long long;

// floyd warshal
class Solution {
public:
    const int n;
    const i64 INF;
    std::vector<std::vector<i64>> dist;

    Solution(int nodes) : n(nodes), INF(1e18) {
        dist = std::vector<std::vector<i64>>(n, std::vector<i64>(n, INF));
    }

    void floyd_warshal() {
        for (int i = 0; i < n; ++i) dist[i][i] = 0;
 
        for (int mid = 0; mid < n; ++mid) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = std::min(dist[i][j], dist[i][mid] + dist[mid][j]);
                }
            }
 
        }
 
    }

    void add_edge(i64 a, i64 b, i64 cost) {
        dist[a][b] = std::min(dist[a][b], cost);
        dist[b][a] = std::min(dist[b][a], cost);
        
    }

    i64 min_dist(int a, int b) {
        return dist[a][b] >= INF ? -1 : dist[a][b];
    }

};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
 
    int n, m, q;
    std::cin >> n >> m >> q;

    Solution sol = Solution(n);
    for (int i = 0; i < m; ++i) {
        i64 a, b, c;
        std::cin >> a >> b >> c;
        --a, --b;

        sol.add_edge(a, b, c);
        sol.add_edge(b, a, c);
    }

    sol.floyd_warshal();
 
    while (q--) {
        int a, b;
        std::cin >> a >> b;
        --a, --b;
        std::cout << sol.min_dist(a, b) << "\n";
    }
}
