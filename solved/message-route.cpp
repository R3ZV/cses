#include <iostream>
#include <vector>
#include <array>
#include <queue>

const int mxN = 1e5;
std::vector<int> adj[mxN];
std::vector<int> parent(mxN, -1);
std::array<bool, mxN> vis;

void bfs(int root) {
    std::queue<int> q;
    q.push(root);
    vis[root] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int u : adj[node]) {
            if (vis[u]) continue;
            parent[u] = node;
            vis[u] = true;
            q.push(u);
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    for (size_t i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    bfs(0);
    if (parent[n - 1] == -1) {
        std::cout << "IMPOSSIBLE\n";
        return 0;
    }
    std::vector<int> path;
    path.reserve(n);

    int curr = n - 1;
    while (parent[curr] != -1) {
        path.push_back(curr + 1);
        curr = parent[curr];
    }
    path.push_back(curr + 1);

    std::cout << path.size() << "\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << " ";
    }
    std::cout << "\n";
}
