#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x0;
    cin >> n >> x0;

    long long L = 0, R = 1000;  
    // since 0 ≤ aᵢ,bᵢ ≤ 1000
    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        L = max(L, a);
        R = min(R, b);
    }

    if (L > R) {
        cout << -1 << "\n";
    } else if (x0 < L) {
        cout << (L - x0) << "\n";
    } else if (x0 > R) {
        cout << (x0 - R) << "\n";
    } else {
        cout << 0 << "\n";
    }

    return 0;
}
