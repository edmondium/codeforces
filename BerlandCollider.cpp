#include <bits/stdc++.h>
using namespace std;

auto binary_search_time = [](auto&& xs, auto&& vs, int s, int m, int e) {
    auto check = [&](double t) {
        double mx = -1e10, mn = 1e10;
        #pragma acc parallel loop reduction(max:mx)
        for (int k = s; k < m; k++) mx = max(mx, xs[k] + vs[k] * t);
        #pragma acc parallel loop reduction(min:mn)
        for (int k = m; k < e; k++) mn = min(mn, xs[k] + vs[k] * t);
        return mx >= mn;
    };
    double lo = 0, hi = 1e11;
    for (int step = 0; step < 100; ++step) {
        double mid = (lo + hi) / 2.0;
        (check(mid) ? hi : lo) = mid;
    }
    return lo;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<long long> xs(n), vs(n);
    for (int i = 0; i < n; i++) cin >> xs[i] >> vs[i];

    double res = 1e11;
    int i = 0;
    while (i < n && vs[i] < 0) i++;
    while (i < n) {
        int j1 = i; while (j1 < n && vs[j1] > 0) j1++;
        if (j1 >= n) break;
        int j2 = j1; while (j2 < n && vs[j2] < 0) j2++;
        res = min(res, binary_search_time(xs, vs, i, j1, j2));
        i = j2;
    }

    if (res >= 1e10) cout << -1 << "\n";
    else cout << fixed << setprecision(12) << res << "\n";
}
