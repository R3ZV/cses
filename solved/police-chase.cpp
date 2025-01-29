#include <iostream>
#include <vector>
#include <array>
#include <assert.h>
#include <limits.h>
#include <queue>
#include <algorithm>
#include <cstring>
 
using i64 = long long;

// police, min cut, ford fulkerso
class Solution {
    const int n;
    std::vector<bool> vis;
    std::vector<std::vector<int>> adj, capacity;
    std::vector<int> parent;

public:
    Solution(int nodes) : n(nodes) {
        vis = std::vector<bool>(n, false);
        adj = std::vector<std::vector<int>>(n);
        capacity = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
        parent = std::vector<int>(n, -1);
    }

    bool reachable() {
        fill(vis.begin(), vis.end(), false);
        fill(parent.begin(), parent.end(), -1);

        std::queue<int> Q;
        Q.push(0);
        vis[0] = true;
        while (!Q.empty()) {
            int i = Q.front();
            Q.pop();
            for (int j : adj[i]) {
                if (capacity[i][j] <= 0 || vis[j]) continue;
                vis[j] = true;
                parent[j] = i;
                Q.push(j);
            }
        }
        return vis[n - 1];
    }

    void add_edge(int from, int to, int cap) {
        adj[from].push_back(to);
        capacity[from][to] += cap;
    }

    void max_flow() {
        while (reachable()) {
            i64 flow = 1e18;
            for (int v = n - 1; v != 0; v = parent[v]) {
                int u = parent[v];
                flow = std::min(flow, (i64)capacity[u][v]);
            }
            for (int v = n - 1; v != 0; v = parent[v]) {
                int u = parent[v];
                capacity[u][v] -= flow;
                capacity[v][u] += flow;
            }
        }
    }

    void res() {
        this->reachable();
        std::vector<std::pair<int, int>> ans;
        for (int i = 0; i < n; i++) {
            for (int x : adj[i]) {
                if (vis[i] && !vis[x]) {
                    ans.push_back({i, x});
                }
            }
        }

        std::cout << ans.size() << '\n';
        for (auto &a : ans) {
            std::cout << a.first + 1 << " " << a.second + 1 << '\n';
        }
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Solution sol = Solution(n);
    for (int i = 0; i < m; ++i) {
        i64 a, b;
        std::cin >> a >> b;
        --a, --b;
        sol.add_edge(a, b, 1);
        sol.add_edge(b, a, 1);
    }
    sol.max_flow();
    sol.res();
}
