#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    // dp[cur][humps][valleys][prev_prev_height][prev_height]
    static ll dp[2][11][11][4][4];
    int cur = 0, nxt = 1;

    // initialize dp[0][0][0][0][0] = 1
    memset(dp, 0, sizeof(dp));
    dp[cur][0][0][0][0] = 1;

    for (int i = 0; i < n; i++) {
        // clear next layer
        for (int h = 0; h <= t; h++)
            for (int v = 0; v < t; v++)
                for (int a = 0; a < 4; a++)
                    for (int b = 0; b < 4; b++)
                        dp[nxt][h][v][a][b] = 0;

        // transition
        for (int h = 0; h <= t; h++) {
            for (int v = 0; v < t; v++) {
                for (int pp = 0; pp < 4; pp++) {
                    for (int p = 0; p < 4; p++) {
                        ll ways = dp[cur][h][v][pp][p];
                        if (!ways) continue;
                        // try next height d in [0..3] representing y in [1..4]
                        for (int d = 0; d < 4; d++) {
                            // forbid flat segment except for the very first step
                            if (i == 0 || d != p) {
                                int nh = h, nv = v;
                                if (i > 1) {
                                    // peak?
                                    if (pp < p && p > d) nh++;
                                    // valley?
                                    if (pp > p && p < d) nv++;
                                }
                                if (nh <= t && nv < t) {
                                    dp[nxt][nh][nv][p][d] += ways;
                                }
                            }
                        }
                    }
                }
            }
        }
        swap(cur, nxt);
    }

    // sum all ways with exactly t peaks and t-1 valleys
    ll ans = 0;
    for (int pp = 0; pp < 4; pp++)
        for (int p = 0; p < 4; p++)
            ans += dp[cur][t][t - 1][pp][p];

    cout << ans << "\n";
    return 0;
}
