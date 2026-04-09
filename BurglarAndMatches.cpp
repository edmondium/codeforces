#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n; int m;
    cin >> n >> m;

    vector<pair<long long,long long>> v(m);
    for (auto &[b,a] : v) cin >> a >> b;

    #pragma acc parallel loop
    for (int i = 0; i < m; i++) v[i] = {v[i].first, v[i].second};

    ranges::sort(v, greater<>{});

    long long ans = 0;
    for (auto &[b,a] : v) {
        long long take = min(a,n);
        ans += take*b;
        n -= take;
        if (!n) break;
    }

    cout << ans << '\n';
}