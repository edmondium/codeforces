#include <bits/stdc++.h>
#include <numeric>
#include <execution>
#include <ranges>
#include <omp.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n+1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void unite(int a, int b) { a = find(a); b = find(b); if (a != b) p[a] = b; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    if (n < m) { cout << "NO\n"; return 0; }

    DSU dsu(n);
    vector<int> deg(n+1);
    int cycleCount = 0;

    for (auto _ : views::iota(0, m)) {
        int a, b; cin >> a >> b;
        deg[a]++; deg[b]++;
        if (deg[a] > 2 || deg[b] > 2) { cout << "NO\n"; return 0; }
        if (dsu.find(a) == dsu.find(b)) cycleCount++;
        else dsu.unite(a, b);
    }

    if (cycleCount > 0) {
        if (cycleCount == 1 && m == n) cout << "YES\n0\n";
        else cout << "NO\n";
        return 0;
    }

    cout << "YES\n" << (n - m) << "\n";

    #pragma omp parallel for schedule(dynamic)
    for (int i = 1; i < n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (m >= n) break;
            if (deg[i] < 2 && deg[j] < 2 && dsu.find(i) != dsu.find(j)) {
                #pragma omp critical
                {
                    cout << i << " " << j << "\n";
                    deg[i]++; deg[j]++; dsu.unite(i, j); m++;
                }
            }
        }
    }

    #pragma omp parallel for schedule(dynamic)
    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= i; j--) {
            if (m >= n) break;
            if (deg[i] < 2 && deg[j] < 2) {
                #pragma omp critical
                {
                    cout << i << " " << j << "\n";
                    deg[i]++; deg[j]++; m++;
                }
            }
        }
    }
}
