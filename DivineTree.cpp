#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;

        // quick global bounds check:
        // minimum sum = base(1) = 1*(1+1)/2 + (n-1) = n
        // maximum sum = cap(n) = n*(n+1)/2
        ll minSum = n;
        ll maxSum = n * (n + 1) / 2;
        if (m < minSum || m > maxSum) {
            cout << -1 << '\n';
            continue;
        }

        // helper lambdas for base(k) and cap(k)
        auto base = [&](ll k) {
            // chain nodes 1..k contribute 1+2+...+k = k*(k+1)/2
            // the rest (n-k) nodes each contribute 1
            return k * (k + 1) / 2 + (n - k);
        };
        auto cap = [&](ll k) {
            // chain nodes sum = k*(k+1)/2
            // rest (n-k) nodes each contribute k
            return k * (k + 1) / 2 + (n - k) * k;
        };

        // find smallest k in [1..n] with cap(k) >= m
        ll lo = 1, hi = n;
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            if (cap(mid) < m)
                lo = mid + 1;
            else
                hi = mid;
        }
        ll k = lo;
        // guaranteed base(k) <= m <= cap(k)

        ll rem = m - base(k);

        // build the tree edges
        // root will be k
        vector<pair<int,int>> edges;
        edges.reserve(n - 1);

        // 1) build the spine (chain) k -> k-1 -> ... -> 1
        //    so for i = 2..k: connect i <-> i-1
        for (int i = 2; i <= k; i++) {
            edges.emplace_back(i, i - 1);
        }

        // 2) attach nodes (k+1 .. n), distributing the extra `rem`
        //    each node i can contribute at most (k-1) extra by attaching under k
        //    if we attach under j in [2..k], it gives j-1 extra over the base=1
        for (int i = k + 1; i <= n; i++) {
            if (rem > 0) {
                ll delta = min(rem, k - 1);
                // we want j-1 = delta  =>  j = delta + 1
                int parent = int(delta + 1);
                edges.emplace_back(parent, i);
                rem -= delta;
            } else {
                // no extra needed, attach to 1 gives divineness = 1
                edges.emplace_back(1, i);
            }
        }

        // output
        cout << k << '\n';
        for (auto &e : edges) {
            cout << e.first << ' ' << e.second << '\n';
        }
    }

    return 0;
}
