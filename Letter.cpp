#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &row : g) 
        cin >> row;

    int rmin = n, rmax = -1, cmin = m, cmax = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '*') {
                rmin = min(rmin, i);
                rmax = max(rmax, i);
                cmin = min(cmin, j);
                cmax = max(cmax, j);
            }
        }
    }

    for (int i = rmin; i <= rmax; i++) {
        cout << g[i].substr(cmin, cmax - cmin + 1) << "\n";
    }
    return 0;
}
