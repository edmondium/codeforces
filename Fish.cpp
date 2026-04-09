#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    static double a[18][18];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    int N = 1 << n;
    static double dp[1 << 18];
    static int pc[1 << 18];
    dp[N - 1] = 1.0;
    for (int m = 1; m < N; m++) pc[m] = pc[m >> 1] + (m & 1);

    #pragma acc parallel loop copy(dp[0:N], pc[0:N], a[0:n][0:n])
    for (int mask = N - 1; mask >= 0; mask--) {
        int k = pc[mask];
        if (k < 2) continue;
        double Pmeet = 1.0 / (k * (k - 1) / 2.0);
        for (int i = 0; i < n; i++) if (mask & (1 << i))
            for (int j = i + 1; j < n; j++) if (mask & (1 << j)) {
                int mj = mask & ~(1 << j);
                int mi = mask & ~(1 << i);
                dp[mj] += dp[mask] * Pmeet * a[i][j];
                dp[mi] += dp[mask] * Pmeet * a[j][i];
            }
    }

    cout << fixed << setprecision(6);
    for (int i = 0; i < n; i++)
        cout << dp[1 << i] << (i + 1 == n ? '\n' : ' ');
}
