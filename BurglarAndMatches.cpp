#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int m;
    cin >> n >> m;

    vector<pair<int,long long>> v(m);
    for (int i = 0; i < m; i++) {
        cin >> v[i].second >> v[i].first; 
        // store as (bᵢ, aᵢ)
    }

    sort(v.begin(), v.end(), greater<>()); 
    long long ans = 0, remaining = n;

    for (auto &p : v) {
        if (remaining == 0) break;
        long long b = p.first, a = p.second;
        long long take = min(a, remaining);
        ans += take * b;
        remaining -= take;
    }

    cout << ans << "\n";
    return 0;
}
