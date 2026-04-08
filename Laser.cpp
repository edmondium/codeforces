#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    ll *n = new ll[t];
    ll *m = new ll[t];
    ll *x1 = new ll[t];
    ll *y1 = new ll[t];
    ll *x2 = new ll[t];
    ll *y2 = new ll[t];
    ll *results = new ll[t];

    for (int i = 0; i < t; i++) {
        cin >> n[i] >> m[i] >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }

    #pragma acc parallel loop copyin(n[0:t],m[0:t],x1[0:t],y1[0:t],x2[0:t],y2[0:t]) copyout(results[0:t])
    for (int i = 0; i < t; i++) {
        ll a = llabs(x1[i] - x2[i]);
        ll b = llabs(y1[i] - y2[i]);
        ll W = n[i] - a;
        ll H = m[i] - b;
        ll overlapW = max(0LL, n[i] - 2*a);
        ll overlapH = max(0LL, m[i] - 2*b);
        ll melted = 2 * W * H - overlapW * overlapH;
        ll total = n[i] * m[i];
        results[i] = total - melted;
    }

    for (int i = 0; i < t; i++) cout << results[i] << '\n';

    delete[] n; delete[] m; delete[] x1; delete[] y1; delete[] x2; delete[] y2; delete[] results;
}
