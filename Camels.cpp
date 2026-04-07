#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;

    static ll dp[2][11][11][4][4];
    int cur = 0, nxt = 1;

    dp[cur][0][0][0][0] = 1;

    for (int i = 0; i < n; i++) {
        #pragma acc parallel loop collapse(4) present(dp)
        for (int h = 0; h <= t; h++)
            for (int v = 0; v < t; v++)
                for (int a = 0; a < 4; a++)
                    for (int b = 0; b < 4; b++)
                        dp[nxt][h][v][a][b] = 0;

        #pragma acc parallel loop collapse(4) present(dp)
        for (int h = 0; h <= t; h++)
            for (int v = 0; v < t; v++)
                for (int pp = 0; pp < 4; pp++)
                    for (int p = 0; p < 4; p++) {
                        ll ways = dp[cur][h][v][pp][p];
                        if (!ways) continue;

                        array<int,4> ds{0,1,2,3};
                        for (int d : ds) {
                            if (i == 0 || d != p) {
                                int nh = h, nv = v;
                                if (i > 1) {
                                    nh += (pp < p && p > d);
                                    nv += (pp > p && p < d);
                                }
                                if (nh <= t && nv < t)
                                    dp[nxt][nh][nv][p][d] += ways;
                            }
                        }
                    }

        swap(cur, nxt);
    }

    ll ans = 0;
    for (int pp = 0; pp < 4; pp++)
        for (int p = 0; p < 4; p++)
            ans += dp[cur][t][t - 1][pp][p];

    cout << ans << "\n";
}
