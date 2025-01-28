#include <iostream>
#include <vector>
#include <array>
#include <queue>

const int mxN = 1e5;
std::vector<int> adj[mxN];
std::vector<int> color(mxN, -1);
std::array<bool, mxN> vis;
bool possible = true;

void dfs(int root, int clr) {
    color[root] = clr;
    for (int u : adj[root]) {
        if (color[u] == color[root]) {
            possible = false;
            continue;
        }
        if (color[u] != -1) continue;
        dfs(u, !clr);
    }
}

// BIPARTIT
int main() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i= 0; i < n; i++) {
        if (color[i] == -1) dfs(i, 0);
    }

    if (!possible) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 0; i < n; i++) std::cout << color[i] + 1 << " ";
    std::cout << "\n";
}
