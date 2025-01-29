#include <iostream>
#include <vector>
#include <array>
#include <assert.h>
#include <limits.h>
#include <queue>
#include <algorithm>
#include <cstring>
 
using i64 = long long;

// dance, boys, girls, matches, bipartit
class Solution {
    const int n;
    std::vector<bool> vis;
    std::vector<std::vector<int>> adj, capacity;
    std::vector<int> parent;

public:
    std::vector<int> match;
    Solution(int nodes) : n(nodes) {
        adj = std::vector<std::vector<int>>(n + 1);
        capacity = std::vector<std::vector<int>>(n + 1, std::vector<int>(n + 1, 0));
        parent = std::vector<int>(n + 1, -1);
        match = std::vector<int>(n + 1, 0);
    }

    bool reachable(int s, int t) {
        fill(parent.begin(), parent.end(), -1);

        std::queue<int> q;
        q.push(s);
        parent[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v: adj[u]){
                if (capacity[u][v] <= 0 || parent[v] != -1) continue;
                parent[v] = u;
                q.push(v);
            }
        }
        return parent[t] != -1;
    }

    void add_edge(int from, int to, int cap) {
        adj[from].push_back(to);
        adj[to].push_back(from);
        capacity[from][to] += cap;
    }

    int max_match(int s, int t){
        int res = 0;
        while (reachable(s, t)){
            int v = t;
            while (v != s){
                capacity[parent[v]][v]--;
                capacity[v][parent[v]]++;
                match[parent[v]] = v;
                v = parent[v];
            }
            ++res;
        }
        return res;
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, k;
    std::cin >> n >> m >> k;
    int s = 0, t = n + m + 1;

    Solution sol = Solution(t);
    for (int i = 1; i <= n; i++) {
        sol.add_edge(s, i, 1);
    }

    for (int i = 1; i <= m; i++) {
        sol.add_edge(n + i, t, 1);
    }

    for (int i = 1; i <= k; i++) {
        int u, v;
        std::cin >> u >> v;

        sol.add_edge(u, n + v, 1);
    }

    std::cout << sol.max_match(s, t) << '\n';
    for(int i = 1; i <= n; i++) {
        if (sol.match[i]) {
            std::cout << i << ' ' << sol.match[i] - n << '\n';
        }
    }
    return 0;
}
