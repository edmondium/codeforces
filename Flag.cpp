#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (auto& row : grid) cin >> row;

    bool uniform = true;
    #pragma acc parallel loop reduction(&:uniform)
    for (int i = 0; i < n; i++) {
        uniform &= ranges::all_of(grid[i], [&](char c){ return c == grid[i][0]; });
    }

    bool adjacent = true;
    #pragma acc parallel loop reduction(&:adjacent)
    for (int i = 1; i < n; i++) {
        adjacent &= (grid[i][0] != grid[i-1][0]);
    }

    cout << (uniform && adjacent ? "YES\n" : "NO\n");
}