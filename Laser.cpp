#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n, m, x1, y1, x2, y2;
        cin >> n >> m >> x1 >> y1 >> x2 >> y2;

        ll a = llabs(x1 - x2);
        ll b = llabs(y1 - y2);

        // Number of distinct columns/rows each laser can cover
        ll W = n - a;
        ll H = m - b;

        // Overlap of their swept rectangles
        ll overlapW = max(0LL, n - 2*a);
        ll overlapH = max(0LL, m - 2*b);

        ll melted = 2 * W * H - overlapW * overlapH;
        ll total = n * m;
        ll unmelted = total - melted;

        cout << unmelted << '\n';
    }
    return 0;
}
