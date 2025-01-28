#include <iostream>
#include <vector>
#include <array>
#include <queue>

using i64 = long long;

// Tree, transpose graph, strongly connected component
// SCC, Kosaraju
class Solution {
    const int n;
    std::vector<std::vector<int>> adj;
    std::vector<bool> vis;

public:
    Solution(int nodes) : n(nodes) {
        adj = std::vector<std::vector<int>>(n);
        vis = std::vector<bool>(n, false);
    }

    void dfs(int root) {
        vis[root] = true;
        for (int u : adj[root]) {
            if (vis[u]) continue;
            dfs(u);
        }
    }

    int explore(int root) {
        dfs(root);
        for (int node = 0; node < n; node++) {
            if (!vis[node]) return node;
        }
        return -1;
    }

    void add_edge(int from, int to) {
        adj[from].push_back(to);
    }
};

// Solution:
// We can simply try a random node and wee if it can reach all the other nodes
// then if it does, we compute the transpose graph and check if it again
// can reach all the other nodes.
//
// Proof:
// 1. If we can't reach a node then we are done. Else
// we know that the node X can reach all other nodes.
//
// So now we only need to know if the other nodes can reach X (If X can reach
// all other nodes, and the other nodes can reach X => any node can reach
// any node via X)
// 
// 2. We compute the transpose graph and we check again if X can reach the other
// nodes (by using the transpose graph we are basically checking if the other
// nodes could reach X).

int main() {
    int n, m;
    std::cin >> n >> m;

    Solution graph = Solution(n);
    Solution t_graph = Solution(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph.add_edge(a - 1, b - 1);
        t_graph.add_edge(b - 1, a - 1);
    }

    int res = graph.explore(0);
    if (res != -1) {
        std::cout << "NO\n";
        std::cout << 1 << " " << res + 1 <<"\n";
        return 0;
    }

    int t_res = t_graph.explore(0);
    if (t_res != -1) {
        std::cout << "NO\n";
        std::cout << t_res + 1 << " " << 1 <<"\n";
        return 0;
    }

    std::cout << "YES\n";
}
