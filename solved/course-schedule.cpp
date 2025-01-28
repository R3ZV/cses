#include <iostream>
#include <vector>
#include <array>
#include <queue>

using i64 = long long;

// Top sort, topological sort
class Solution {
    const int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> in_deg;

public:
    Solution(int nodes) : n(nodes) {
        adj = std::vector<std::vector<int>>(n);
        in_deg = std::vector<int>(n);
    }

    std::vector<int> top_sort() {
        std::vector<int> res;
        std::queue<int> Q;
        for (int node = 0; node < n; node++) {
            if (in_deg[node] == 0) {
                Q.push(node);
            }
        }
        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();
            res.push_back(node);
            for (int u : adj[node]) {
                in_deg[u]--;
                if (in_deg[u] == 0) {
                    Q.push(u);
                }
            }

        }
        return res;
    }

    void add_edge(int from, int to) {
        adj[from].push_back(to);
        in_deg[to]++;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Solution graph = Solution(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph.add_edge(a - 1, b - 1);
    }

    std::vector<int> sorted = graph.top_sort();
    if (sorted.size() != n) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }
    for (int x : sorted) std::cout << x + 1 << " ";
    std::cout << "\n";

}
