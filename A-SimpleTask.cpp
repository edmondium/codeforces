#include <bits/stdc++.h>
#include <bit>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int N = 1 << n;

    vector<vector<long long>> f(N, vector<long long>(n));
    vector<vector<bool>> g(n, vector<bool>(n));

    for (int e = 0; e < m; ++e) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        g[x][y] = g[y][x] = true;
        if (x > y) swap(x, y);
        f[(1 << x) | (1 << y)][y]++;
    }

    long long total = 0;

    #pragma omp parallel for reduction(+:total) schedule(dynamic)
    for (int mask = 0; mask < N; ++mask) {
        if (__builtin_popcount(mask) < 2) continue;
        int start = std::countr_zero(static_cast<unsigned>(mask));
        for (int j = start + 1; j < n; ++j) {
            if (!(mask & (1 << j))) continue;
            int pm = mask ^ (1 << j);
            long long ways = 0;
            for (int u = start + 1; u < n; ++u) {
                if (u != j && (pm & (1 << u)) && g[u][j]) ways += f[pm][u];
            }
            f[mask][j] += ways;
            if (g[j][start]) total += ways;
        }
    }

    cout << (total / 2) << "\n";
}
