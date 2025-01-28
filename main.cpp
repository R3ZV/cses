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

int main() {
    int n, m;
    std::cin >> n >> m;
    int cnt = n, mx = 1;
    DSU dsu = DSU(n);
    while (m--) {
        int a, b;
        std::cin >> a >> b;
        --a, --b;
        if (dsu.join(a, b)) {
          --cnt;
          mx = std::max(mx, dsu.size(a));
        }
        std::cout << cnt << ' ' << mx << "\n";
    }
    return 0;
}
