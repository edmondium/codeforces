#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, A, B;
    cin >> n >> A >> B;
    vector<int> h(n + 2);
    for (int i = 1; i <= n; i++) cin >> h[i];

    int m = n - 2;
    const int MAXX = 16;

    if (m == 1) {
        int L1 = (h[1] + B) / B;
        int L3 = (h[3] + B) / B;
        int L2 = (h[2] + A) / A;
        int best = INF, x1 = 0;
        for (int x = max({L1, L3, L2}); x <= MAXX; x++)
            if (A * x > h[2] && x < best) best = x, x1 = x;
        cout << best << "\n";
        ranges::for_each(views::iota(0, best), [&](int i) {
            cout << 2 << (i + 1 < best ? ' ' : '\n');
        });
        return 0;
    }

    static int dp[11][17][17];
    static pair<int,int> par[11][17][17];
    for (int c = 0; c <= m; c++)
        for (int p = 0; p <= MAXX; p++)
            for (int q = 0; q <= MAXX; q++)
                dp[c][p][q] = INF;

    int L1 = (h[1] + B) / B;
    for (int x = L1; x <= MAXX; x++) {
        dp[1][0][x] = x;
        par[1][0][x] = {-1, -1};
    }

    for (int c = 1; c < m; c++) {
        int j = c + 1;
        #pragma omp parallel for collapse(2)
        for (int p = 0; p <= MAXX; p++) {
            for (int q = 0; q <= MAXX; q++) {
                if (dp[c][p][q] == INF) continue;
                int used = dp[c][p][q];
                int need = h[j] - A * q - B * p + 1;
                int LB = need > 0 ? (need + B - 1) / B : 0;
                for (int r = LB; r <= MAXX; r++) {
                    int cand = used + r;
                    if (cand < dp[c+1][q][r]) {
                        #pragma omp critical
                        {
                            if (cand < dp[c+1][q][r]) {
                                dp[c+1][q][r] = cand;
                                par[c+1][q][r] = {p, q};
                            }
                        }
                    }
                }
            }
        }
    }

    int Llast = (h[n] + B) / B;
    int ans = INF, bp = 0, bq = 0;
    for (int p = 0; p <= MAXX; p++)
        for (int q = 0; q <= MAXX; q++) {
            int val = dp[m][p][q];
            if (val == INF) continue;
            if (A * q + B * p <= h[n-1]) continue;
            if (q < Llast) continue;
            if (val < ans) ans = val, bp = p, bq = q;
        }

    vector<int> x(m + 1);
    x[m] = bq;
    x[m-1] = bp;
    int cp = bp, cq = bq;
    for (int c = m; c > 1; c--) {
        auto [pp, pq] = par[c][cp][cq];
        if (c - 2 >= 1) x[c-2] = pp;
        cp = pp; cq = pq;
    }

    cout << ans << "\n";
    ranges::for_each(views::iota(1, m+1), [&](int i) {
        ranges::for_each(views::iota(0, x[i]), [&](int) {
            cout << (i+1) << " ";
        });
    });
    cout << "\n";
}
