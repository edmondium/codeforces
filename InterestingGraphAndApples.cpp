#include <iostream>
#include <vector>
#include <numeric>   // for std::iota
#include <algorithm>

class DSU {
  std::vector<int> p;
public:
  DSU(int n): p(n+1) {
    std::iota(p.begin(), p.end(), 0);
  }
  int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
  }
  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) p[a] = b;
  }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    // Quick impossible check
    if (n < m) {
        std::cout << "NO\n";
        return 0;
    }

    DSU dsu(n);
    std::vector<int> deg(n+1, 0);
    int cycleCount = 0;

    // Read edges, update degrees and DSU
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        // loops count double
        deg[a]++;
        deg[b]++;

        if (deg[a] > 2 || deg[b] > 2) {
            std::cout << "NO\n";
            return 0;
        }

        if (dsu.find(a) == dsu.find(b)) {
            // this edge closes a cycle
            cycleCount++;
        } else {
            dsu.unite(a, b);
        }
    }

    // If we already have cycles, check special case
    if (cycleCount > 0) {
        if (cycleCount == 1 && m == n) {
            std::cout << "YES\n0\n";
        } else {
            std::cout << "NO\n";
        }
        return 0;
    }

    // Otherwise we need to add exactly (n-m) edges
    std::cout << "YES\n" << (n - m) << "\n";

    // First, connect different components until we form one cycle
    for (int i = 1; i < n; i++) {
        for (int j = i+1; j <= n && (int)(n - m) > 0; j++) {
            if (deg[i] < 2 && deg[j] < 2 && dsu.find(i) != dsu.find(j)) {
                std::cout << i << " " << j << "\n";
                deg[i]++; 
                deg[j]++;
                dsu.unite(i, j);
                m++;
            }
        }
    }

    // Then, if we still need edges, add them (possibly loops or parallels)
    for (int i = 1; i <= n && m < n; i++) {
        for (int j = n; j >= i && m < n; j--) {
            if (deg[i] < 2 && deg[j] < 2) {
                std::cout << i << " " << j << "\n";
                deg[i]++;
                deg[j]++;
                m++;
            }
        }
    }

    return 0;
}
