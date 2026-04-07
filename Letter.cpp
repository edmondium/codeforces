#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> g(n);
    for (auto &s : g) cin >> s;

    int rmin = n, rmax = -1, cmin = m, cmax = -1;

    #pragma acc parallel loop reduction(min:rmin,cmin) reduction(max:rmax,cmax)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '*') {
                rmin = rmin < i ? rmin : i;
                rmax = rmax > i ? rmax : i;
                cmin = cmin < j ? cmin : j;
                cmax = cmax > j ? cmax : j;
            }
        }
    }

    for (int i : views::iota(rmin, rmax + 1))
        cout << string_view(g[i]).substr(cmin, cmax - cmin + 1) << '\n';
}
