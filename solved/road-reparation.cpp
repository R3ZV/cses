#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>

using i64 = long long;

// dsu
class DSU {
  std::vector<int> sz;
  std::vector<int> rep;
 
public:
  DSU(int n) {
    sz = std::vector<int>(n);
    rep = std::vector<int>(n);
    
    for (int node = 0; node < n; node++) {
      sz[node] = 1;
      rep[node] = node;
    }
  }
 
  int size(int a) {
    return sz[find(a)];
  }
 
  int find(int a) {
    if (a == rep[a]) return a;
    return rep[a] = find(rep[a]);
  }
 
  bool same(int a, int b) {
    return find(a) == find(b);
  }
 
  bool join(int a, int b) {
    a = find(a);
    b = find(b);
 
    if (a == b) return false;
    if (sz[a] < sz[b]) std::swap(a, b);
 
    rep[b] = a;
    sz[a] += sz[b];
    return true;
  }
};

// kruskal
std::pair<int, i64> kruskal(int n, std::vector<std::array<i64, 3>> &edges) {
  DSU dsu(n);
  std::sort(edges.begin(), edges.end());

  i64 apm_cost = 0;
  int cnt = 0;
  for (std::array<i64, 3> edge : edges) {
      i64 cost = edge[0];
      i64 from = edge[1];
      i64 to = edge[2];

      if (dsu.join(from, to)) {
          apm_cost += cost;
          ++cnt;
      }
  }
  return {cnt, apm_cost};
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::array<i64, 3>> edg;
    for (int i = 0; i < m; i++) {
        i64 a, b, c;
        std::cin >> a >> b >> c;
        --a, --b;
        edg.push_back({c, a, b});
    }

    std::pair<int, i64> res  = kruskal(n, edg);
    int cnt = res.first;
    i64 cost = res.second;
    if (cnt == n - 1) {
      std::cout << cost << "\n";
    } else {
      std::cout << "IMPOSSIBLE\n";
    }
    return 0;
}
