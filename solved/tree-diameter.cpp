#include <iostream>
#include <vector>
#include <array>
#include <queue>

using i64 = long long;

// Tree diameter
class Solution {
    const int n;
    std::vector<std::vector<int>> adj;

public:
    Solution(int nodes) : n(nodes) {
        adj = std::vector<std::vector<int>>(n);
    }

    void add_edge(int from, int to) {
        adj[from].push_back(to);
        adj[to].push_back(from);
    }

    int bfs(int root, bool want_dist) {
        std::queue<int> Q;
        Q.push(root);

        std::vector<bool> vis(n, false);
        vis[root] = true;

        std::vector<int> dist(n, 2e6);
        dist[root] = 0;

        int last = root;
        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();

            for (int u : adj[node]) {
                if (vis[u]) continue;
                vis[u] = true;
                dist[u] = dist[node] + 1;
                Q.push(u);
            }
            last = node;
        }

        if (want_dist) {
            return dist[last];
        }
        return last;
    }

    void print() {
        int ext = bfs(0, false);
        std::cout << bfs(ext, true) << "\n";
    }
};

int main() {
    int n;
    std::cin >> n;

    Solution sol = Solution(n);
    for (int i = 1; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        sol.add_edge(a - 1, b - 1);
    }

    sol.print();

}
