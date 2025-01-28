#include <iostream>
#include <vector>
#include <array>
#include <queue>

using i64 = long long;

const int mxN = 2e5 + 1;

std::vector<int> adj[mxN];
std::vector<i64> sz(mxN, 0);

void dfs(int root) {
    for (int u : adj[root]) {
        dfs(u);
        sz[root] += sz[u] + 1;
    }
}

// Number of children per node / parent
int main() {
    int n;
    std::cin >> n;

    for (int i = 1; i < n; i++) {
        int par;
        std::cin >> par;
        par--;
        adj[par].push_back(i);
    }

    dfs(0);

    for (int i = 0; i < n; i++) {
        std::cout << sz[i] << " ";
    }
    std::cout << "\n";

}
