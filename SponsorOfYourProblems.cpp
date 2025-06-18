#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string L, R;
        cin >> L >> R;
        int n = L.size();

        // dp[tl][th]: current position's DP
        // tl = tight to L (haven't gone above it), th = tight to R
        vector<array<int,2>> dp(2), ndp(2);
        for(int tl=0; tl<2; tl++)
            for(int th=0; th<2; th++)
                dp[tl][th] = INF;
        dp[1][1] = 0;

        for (int pos = 0; pos < n; pos++) {
            for(int tl=0; tl<2; tl++)
                for(int th=0; th<2; th++)
                    ndp[tl][th] = INF;

            for (int tl = 0; tl < 2; tl++) {
                for (int th = 0; th < 2; th++) {
                    int base = dp[tl][th];
                    if (base == INF) continue;

                    // digit bounds
                    int lo = tl ? (L[pos]-'0') : 0;
                    int hi = th ? (R[pos]-'0') : 9;
                    for (int d = lo; d <= hi; d++) {
                        if (pos == 0 && d == 0) continue; // no leading zero
                        int cost = (d == L[pos]-'0') + (d == R[pos]-'0');
                        int ntl = tl & (d == L[pos]-'0');
                        int nth = th & (d == R[pos]-'0');
                        ndp[ntl][nth] = min(ndp[ntl][nth], base + cost);
                    }
                }
            }
            dp.swap(ndp);
        }

        // take best of the four end states
        int ans = INF;
        for(int tl=0; tl<2; tl++)
            for(int th=0; th<2; th++)
                ans = min(ans, dp[tl][th]);

        cout << ans << "\n";
    }
    return 0;
}
