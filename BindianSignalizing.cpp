#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &v : a) cin >> v;

    auto it = ranges::max_element(a);
    int pos = it - a.begin();
    int globalVal = *it;

    vector<int> b(n + 1);
    ranges::for_each(views::iota(0, n), [&](int i) { b[i] = a[(pos + i) % n]; });
    b[n] = b[0];

    vector<int> l(n), r(n + 1), s(n + 1);
    r[n] = n; s[n] = 0;

    #pragma omp parallel for schedule(dynamic)
    for (int i = n - 1; i >= 0; --i) {
        r[i] = i + 1;
        while (r[i] < n && b[i] > b[r[i]]) r[i] = r[r[i]];
        while (r[i] < n && b[i] == b[r[i]]) {
            s[i] = s[r[i]] + 1;
            r[i] = r[r[i]];
        }
    }

    l[0] = 0;
    #pragma omp parallel for schedule(dynamic)
    for (int i = 1; i < n; ++i) {
        l[i] = i - 1;
        while (l[i] > 0 && b[i] >= b[l[i]]) l[i] = l[l[i]];
    }

    long long ans = 0;
    #pragma omp parallel for reduction(+:ans)
    for (int i = 0; i < n; ++i) {
        ans += s[i];
        if (b[i] < b[0]) {
            if (l[i] == 0 && r[i] == n) ans += 1;
            else ans += 2;
        }
    }

    cout << ans << "\n";
}
