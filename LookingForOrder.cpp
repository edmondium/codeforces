#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int xs, ys;
    cin >> xs >> ys;

    int n;
    cin >> n;
    vector<pair<int,int>> pt(n+1);
    pt[0] = {xs, ys};
    for(int i=1; i<=n; i++){
        cin >> pt[i].first >> pt[i].second;
    }

    // Precompute squared distances
    vector<ll> d0(n+1);
    vector<vector<ll>> d(n+1, vector<ll>(n+1, 0));
    for(int i=1; i<=n; i++){
        ll dx = pt[i].first - xs;
        ll dy = pt[i].second - ys;
        d0[i] = dx*dx + dy*dy;
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            ll dx = pt[i].first - pt[j].first;
            ll dy = pt[i].second - pt[j].second;
            d[i][j] = dx*dx + dy*dy;
        }
    }

    int FULL = 1<<n;
    const ll INF = LLONG_MAX/4;
    vector<ll> dp(FULL, INF);
    vector<pair<int,int>> choice(FULL, {-1,-1});
    dp[0] = 0;

    for(int mask=1; mask<FULL; mask++){
        // find lowest bit i
        int i = __builtin_ctz(mask) + 1; // 1-based index
        int bit_i = 1 << (i-1);

        // Option A: take i alone
        ll costA = dp[mask ^ bit_i] + 2 * d0[i];
        dp[mask] = costA;
        choice[mask] = {i, 0};

        // Option B: pair i with some j>i in mask
        int rest = mask ^ bit_i;
        for(int sub = rest; sub; sub &= (sub-1)){
            int j = __builtin_ctz(sub) + 1;
            int bit_j = 1 << (j-1);
            ll costB = dp[mask ^ bit_i ^ bit_j]
                     + d0[i] + d[i][j] + d0[j];
            if(costB < dp[mask]){
                dp[mask] = costB;
                choice[mask] = {i, j};
            }
        }
    }

    // Output minimal total cost
    cout << dp[FULL-1] << "\n";

    // Reconstruct trips
    int mask = FULL-1;
    vector<int> path;
    while(mask){
        auto [i,j] = choice[mask];
        // each trip: 0 -> i -> (j?) -> 0
        path.push_back(0);
        path.push_back(i);
        if(j) path.push_back(j);
        // returned to 0 implicitly by next 0 or by end
        mask ^= (1<<(i-1));
        if(j) mask ^= (1<<(j-1));
    }
    path.push_back(0);

    // Print sequence
    for(int x: path) cout << x << " ";
    cout << "\n";
    return 0;
}
