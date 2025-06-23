#include <bits/stdc++.h>
#include <bit>  // for std::countr_zero
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int N = 1 << n;

    // f[mask][v]: number of simple paths covering exactly 'mask' that end at v
    vector<vector<long long>> f(N, vector<long long>(n, 0));
    vector<vector<bool>> g(n, vector<bool>(n, false));

    // read edges, init length-1 paths
    for (int e = 0; e < m; ++e) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        g[x][y] = g[y][x] = true;
        if (x > y) swap(x, y);
        f[(1 << x) | (1 << y)][y]++;
    }

    long long total = 0;
    for (int mask = 0; mask < N; ++mask) {
        if (mask < 3) continue;  // need at least two bits to form a cycle

        // find the smallest-set bit: that's our "start" vertex
        int start = std::countr_zero(static_cast<unsigned>(mask));

        // try every possible 'end' j > start with no incoming paths yet
        for (int j = start + 1; j < n; ++j) {
            if (!(mask & (1 << j))) continue;
            if (f[mask][j] != 0) continue;

            // build all paths that end at j by extending shorter masks
            int pm = mask ^ (1 << j);
            long long ways = 0;
            for (int u = start + 1; u < n; ++u) {
                if (u == j) continue;
                if ((pm & (1 << u)) && g[u][j]) {
                    ways += f[pm][u];
                }
            }
            f[mask][j] = ways;

            // if j connects back to start, we've closed a cycle
            if (g[j][start]) {
                total += ways;
            }
        }
    }

    // each undirected cycle was counted twice
    cout << (total / 2) << "\n";
    return 0;
}
