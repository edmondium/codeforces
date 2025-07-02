#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 a, b, x, y;
    cin >> a >> b >> x >> y;

    int64 g = gcd(x, y);
    x /= g;
    y /= g;

    // Maximum k so that k*x <= a and k*y <= b
    int64 k = min(a / x, b / y);
    if (k > 0) {
        cout << (k * x) << " " << (k * y) << "\n";
    } else {
        cout << "0 0\n";
    }

    return 0;
}
