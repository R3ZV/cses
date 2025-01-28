#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>

using i64 = long long;

// cycle, distinct nodes
class Solution {
public:
    const int n;

    const int WHITE = 0;
    const int GRAY = 1;
    const int BLACK = 2;

    std::vector<std::vector<int>> adj;
    std::vector<int> p;
    std::vector<int> color;
    std::pair<int, int> cycle = {-1, -1};

    Solution(int nodes) : n(nodes) {
        adj = std::vector<std::vector<int>>(n);
        p = std::vector<int>(n);
        color = std::vector<int>(n, WHITE);
        cycle = {-1, -1};
 
    }
 
    bool dfs(int v) {
        color[v] = GRAY;
        for (int u : adj[v]) {
            if (color[u] == WHITE) {
                p[u] = v;
                if (dfs(u)) {
                    return true;
                }
            } else if (color[u] == GRAY) {
                cycle = { u, v };
                return true;
            }
        }
        color[v] = BLACK;
        return false;
    }
 
    void find_cycle() {
        for (int node = 0; node < n; node++) {
            if (color[node] == WHITE && dfs(node)) {
                break;
            }
        }

        if (cycle.first == -1) {
            std::cout << "IMPOSSIBLE" << "\n";
            return;
        }

        std::vector<int> ans;
        ans.push_back(cycle.first);

        for (int v = cycle.second; v != cycle.first; v = p[v]) {
            ans.push_back(v);
        }

        ans.push_back(cycle.first);
        std::reverse(ans.begin(), ans.end());

        std::cout << ans.size() << "\n";
        for (int x: ans) {
            std::cout << x + 1 << ' ';
        }
        std::cout << "\n";
    }

    void add_edge(int a, int b) {
        adj[a].push_back(b);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Solution sol = Solution(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        --a, --b;
        sol.add_edge(a, b);
    }
    sol.find_cycle();
}
