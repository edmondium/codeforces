#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, j, k;
        cin >> n >> j >> k;
        vector<int> a(n);
        for (auto &x : a) cin >> x;

        int threshold = a[j - 1];
        int m = 0;
        for (int x : a)
            if (x > threshold)
                ++m;

        bool ok = (k > 1) || (m == 0);
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
