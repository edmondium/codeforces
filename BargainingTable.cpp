#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &row : g) cin >> row;
    int ans = 0;
    #pragma acc parallel loop collapse(2) reduction(max:ans)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (g[i][j] == '0')
                for (int x = i; x < n; x++)
                    for (int y = j; y < m; y++) {
                        bool ok = true;
                        for (int a = i; a <= x && ok; a++)
                            for (int b = j; b <= y; b++)
                                if (g[a][b] == '1') { ok = false; break; }
                        if (ok) ans = max(ans, 2 * ((x - i + 1) + (y - j + 1)));
                    }
    cout << ans << "\n";
}
