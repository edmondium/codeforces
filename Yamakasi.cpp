#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Count subarrays of a[L..R-1] whose sum == target,
// in O(len log len) time instead of unordered_map.
ll countSumFast(const vector<ll>& a, int L, int R, ll target) {
    int len = R - L;
    // 1) build prefix sums P[0..len]
    vector<ll> P(len+1, 0);
    for(int i = 0; i < len; i++)
        P[i+1] = P[i] + a[L+i];

    // 2) collect & compress all P values
    vector<ll> vals = P;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    // 3) freq array over compressed coords
    int M = vals.size();
    vector<int> freq(M, 0);

    auto idx = [&](ll x){
        // find compressed index of x in vals[], or -1 if not present
        auto it = lower_bound(vals.begin(), vals.end(), x);
        return it!=vals.end() && *it==x
            ? int(it - vals.begin())
            : -1;
    };

    // initial: P[0]==0 seen once
    ll res = 0;
    int i0 = idx(P[0]);
    freq[i0] = 1;

    // sweep i=1..len
    for(int i = 1; i <= len; i++){
        // we want count of previous P[j] == P[i] - target
        int j = idx(P[i] - target);
        if (j != -1)
            res += freq[j];

        // now mark P[i] seen
        int k = idx(P[i]);
        freq[k]++;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n; ll s, x;
        cin >> n >> s >> x;
        vector<ll> a(n);
        for(auto &v : a) cin >> v;

        ll ans = 0;
        // we'll build "chunks" where all a[i] <= x
        int i = 0;
        while(i < n){
            if (a[i] > x) { i++; continue; }
            // find end j of this chunk [i..j)
            int j = i;
            while(j < n && a[j] <= x) j++;

            // (A) count all subarrays in [i..j) summing to s
            ll total = countSumFast(a, i, j, s);

            // (B) subtract those that never touch a[k]==x
            ll noX = 0;
            int subL = i;
            for(int k = i; k < j; k++){
                if (a[k] == x){
                    if (subL < k)
                        noX += countSumFast(a, subL, k, s);
                    subL = k+1;
                }
            }
            if (subL < j)
                noX += countSumFast(a, subL, j, s);

            ans += (total - noX);
            i = j;
        }

        cout << ans << "\n";
    }
    return 0;
}
