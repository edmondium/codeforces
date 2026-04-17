#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    long long total = accumulate(a.begin(), a.end(), 0LL);
    if (total % 3 != 0) {
        cout << 0 << '\n';
        return 0;
    }

    long long target = total / 3, twoTarget = 2 * target;
    vector<long long> prefix(n);
    partial_sum(a.begin(), a.end(), prefix.begin());

    long long ways = 0, countTarget = 0;

    #pragma acc parallel loop reduction(+:ways,countTarget)
    for (int i = 0; i < n - 1; i++) {
        if (prefix[i] == twoTarget) ways += countTarget;
        if (prefix[i] == target) countTarget++;
    }

    cout << ways << '\n';
}
