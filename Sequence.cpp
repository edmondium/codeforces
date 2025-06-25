#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL<<62);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<ll> a(N), b;
    for(int i = 0; i < N; i++){
        cin >> a[i];
        b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    // b may have duplicates; that's fine.

    // prev[k] = dp[i-1][k], cur[k] = dp[i][k]
    vector<ll> prev(N, 0), cur(N, INF);

    // Base: i=0, cost to change a[0] to b[k]
    for(int k = 0; k < N; k++){
        prev[k] = llabs(a[0] - b[k]);
        if(k) prev[k] = min(prev[k], prev[k-1]);
    }

    // DP for i=1..N-1
    for(int i = 1; i < N; i++){
        ll best = INF;
        for(int k = 0; k < N; k++){
            // best = min_{j≤k} prev[j]
            best = min(best, prev[k]);
            // change a[i] -> b[k] + best of prev
            cur[k] = best + llabs(a[i] - b[k]);
        }
        // prefix-min cur so that next iteration can use non-decreasing
        for(int k = 1; k < N; k++){
            cur[k] = min(cur[k], cur[k-1]);
        }
        swap(prev, cur);
    }

    // answer = min_k dp[N-1][k]
    cout << prev[N-1] << "\n";
    return 0;
}
