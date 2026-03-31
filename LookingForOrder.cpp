#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int xs, ys, n;
    cin >> xs >> ys >> n;
    vector<pair<int,int>> pt(n+1);
    pt[0] = {xs, ys};
    for (int i=1; i<=n; i++) cin >> pt[i].first >> pt[i].second;

    vector<ll> d0(n+1);
    vector<vector<ll>> d(n+1, vector<ll>(n+1));
    ranges::for_each(views::iota(1,n+1), [&](int i){
        ll dx = pt[i].first - xs, dy = pt[i].second - ys;
        d0[i] = dx*dx + dy*dy;
    });
    ranges::for_each(views::iota(1,n+1), [&](int i){
        ranges::for_each(views::iota(1,n+1), [&](int j){
            ll dx = pt[i].first - pt[j].first, dy = pt[i].second - pt[j].second;
            d[i][j] = dx*dx + dy*dy;
        });
    });

    int FULL = 1<<n;
    const ll INF = LLONG_MAX/4;
    vector<ll> dp(FULL, INF);
    vector<pair<int,int>> choice(FULL);
    dp[0] = 0;

    #pragma omp parallel for schedule(dynamic)
    for (int mask=1; mask<FULL; mask++) {
        int i = __builtin_ctz(mask) + 1;
        int bit_i = 1 << (i-1);
        ll costA = dp[mask ^ bit_i] + 2*d0[i];
        dp[mask] = costA;
        choice[mask] = {i,0};
        int rest = mask ^ bit_i;
        for (int sub=rest; sub; sub&=(sub-1)) {
            int j = __builtin_ctz(sub) + 1;
            int bit_j = 1 << (j-1);
            ll costB = dp[mask ^ bit_i ^ bit_j] + d0[i] + d[i][j] + d0[j];
            if (costB < dp[mask]) {
                dp[mask] = costB;
                choice[mask] = {i,j};
            }
        }
    }

    cout << dp[FULL-1] << "\n";
    int mask = FULL-1;
    vector<int> path;
    while (mask) {
        auto [i,j] = choice[mask];
        path.push_back(0);
        path.push_back(i);
        if (j) path.push_back(j);
        mask ^= (1<<(i-1));
        if (j) mask ^= (1<<(j-1));
    }
    path.push_back(0);
    for (int x: path) cout << x << " ";
    cout << "\n";
}
