#include <iostream>
#include <vector>
#include <array>
#include <limits.h>
#include <queue>
#include <algorithm>
 
using i64 = long long;
 
// edmon-karp, ford-fulkerson, max flow, min cut
class Solution {
    const int n;
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<i64>> capacity;

public:
    Solution(int nodes) : n(nodes) {
        adj = std::vector<std::vector<int>>(n);
        capacity = std::vector<std::vector<i64>>(n, std::vector<i64>(n, 0));
    }

    i64 max_flow(int source, int sink) {
        std::vector<int> parent(n, -1);

        // path from source to sink
        // no non-negative capacities
        auto reachable = [&]() -> bool {
            std::queue<int> q;
            q.push(source);
            while (!q.empty()) {
                int node = q.front();
                q.pop();
                for (int son : adj[node]) {
                    i64 w = capacity[node][son];
                    if (w <= 0 || parent[son] != -1) continue;
                    parent[son] = node;
                    q.push(son);
                }
            }
            return parent[sink] != -1;
        };

        long long flow = 0;
        while (reachable()) {
            i64 curr_flow = LLONG_MAX;
            int node = sink;
            while (node != source) {
                curr_flow = std::min(curr_flow, capacity[parent[node]][node]);
                node = parent[node];
            }

            node = sink;
            while (node != source) {
                // update flow for the edge
                capacity[parent[node]][node] -= curr_flow;

                // update flow for residual edge
                capacity[node][parent[node]] += curr_flow;

                node = parent[node];
            }
            flow += curr_flow;
            std::fill(parent.begin(), parent.end(), -1);
        }

        return flow;
    }

    void add_edge(int from, int to, int cap) {
        adj[from].push_back(to);
        capacity[from][to] += cap;

        // residual edge
        adj[to].push_back(from);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    Solution sol = Solution(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        --a, --b;
        sol.add_edge(a, b, c);
    }

    std::cout << sol.max_flow(0, n - 1) << "\n";
}
