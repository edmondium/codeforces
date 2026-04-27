#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(m+1);
    for (int i = 1; i <= m; i++) cin >> a[i];

    vector<vector<long double>> C(n+1, vector<long double>(n+1));
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= i; j++)
            C[i][j] = (j==0||j==i)?1:C[i-1][j-1]+C[i-1][j];

    vector dp(n+1, vector(m+1, vector<long double>(n+1)));
    dp[0][0][0] = 1;

    #pragma acc parallel loop collapse(3)
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k <= n; k++)
                if (dp[i][j][k] > 0) {
                    for (int c = 0; c <= n - i; c++) {
                        long double p = C[n-i][c] * powl(1.0L/(m-j), c) * powl((long double)(m-j-1)/(m-j), (n-i-c));
                        int q = (c + a[j+1] - 1) / a[j+1];
                        int nk = max(k, q);
                        dp[i+c][j+1][nk] += dp[i][j][k] * p;
                    }
                }

    long double ans = 0;
    for (int k = 0; k <= n; k++)
        ans += k * dp[n][m][k];

    cout << fixed << setprecision(12) << ans;
}
