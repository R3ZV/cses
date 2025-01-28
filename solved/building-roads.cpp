#include <iostream>
#include <vector>
#include <array>

const int mxN = 1e5;
std::vector<int> adj[mxN];
std::array<bool, mxN> vis;

void dfs(int root) {
    vis[root] = true;
    for (int u : adj[root]) {
        if (vis[u]) continue;
        dfs(u);
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    for (size_t i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;

        a--;
        b--;
    
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    std::vector<int> leaders;
    leaders.reserve(mxN);

    for (int root = 0; root < n; root++) {
        if (vis[root]) continue;
        dfs(root);
        leaders.push_back(root);
    }

    std::cout << leaders.size() - 1 << "\n";
    for (size_t i = 1; i < leaders.size(); i++) {
        std::cout << leaders[i - 1] + 1 << " " << leaders[i] + 1 << "\n";
    }
    return 0;
}
