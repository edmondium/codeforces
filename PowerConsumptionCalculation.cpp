#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long p1, p2, p3, t1, t2;
    cin >> n >> p1 >> p2 >> p3 >> t1 >> t2;

    vector<pair<int,int>> intervals(n);
    for (auto& [l,r] : intervals) cin >> l >> r;

    auto idle_power = [&](int idle) {
        long long normal = min<long long>(idle, t1);
        long long saver = min<long long>(max(0, idle - (int)t1), t2);
        long long sleep = max(0, idle - (int)t1 - (int)t2);
        return normal * p1 + saver * p2 + sleep * p3;
    };

    long long total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < n; i++) {
        total += 1LL * (intervals[i].second - intervals[i].first) * p1;
        if (i < n - 1) total += idle_power(intervals[i+1].first - intervals[i].second);
    }

    cout << total << "\n";
}
