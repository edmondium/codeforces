#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x0;
    cin >> n >> x0;

    vector<pair<long long,long long>> seg(n);
    for (auto& [a,b] : seg) {
        cin >> a >> b;
        if (a > b) swap(a,b);
    }

    long long L = LLONG_MIN, R = LLONG_MAX;

    #pragma acc parallel loop reduction(max:L) reduction(min:R)
    for (int i = 0; i < n; i++) {
        L = max(L, seg[i].first);
        R = min(R, seg[i].second);
    }

    long long ans =
        (L > R) ? -1 :
        (x0 < L ? L - x0 :
        (x0 > R ? x0 - R : 0));

    cout << ans;
}
