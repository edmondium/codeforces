#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, j;
    cin >> n >> j;
    long long x, y;
    cin >> x >> y;
    vector<pair<long long,long long>> a(n);
    for (auto &p : a) cin >> p.first >> p.second;

    j %= 2 * n;

    auto *ax = new long long[n];
    auto *ay = new long long[n];
    for (int i = 0; i < n; i++) {
        ax[i] = a[i].first;
        ay[i] = a[i].second;
    }

    #pragma acc parallel loop copy(x,y) copyin(ax[0:n],ay[0:n])
    for (long long i = 0; i < j; i++) {
        x = 2 * ax[i % n] - x;
        y = 2 * ay[i % n] - y;
    }

    cout << x << " " << y << "\n";

    delete[] ax;
    delete[] ay;
}
