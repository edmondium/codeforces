#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
const ull BASE = 100003;

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto &x : a) { cin >> x; }
    b = a;

    ranges::sort(b);
    b.erase(unique(b.begin(), b.end()), b.end());

    vector<ull> h(n+1), pw(n+1);
    pw[0] = 1;

    ranges::for_each(views::iota(0,n), [&](int i){
        a[i] = int(ranges::lower_bound(b, a[i]) - b.begin());
        h[i+1] = h[i]*BASE + (a[i]+1);
        pw[i+1] = pw[i]*BASE;
    });

    auto get = [&](int l, int r) {
        return h[r] - h[l]*pw[r-l];
    };

    vector<vector<int>> pos(b.size());
    ranges::for_each(views::iota(0,n), [&](int i){ pos[a[i]].push_back(i); });

    vector<pair<int,int>> repeats;
    ranges::for_each(views::iota(0,n), [&](int i){
        for (int j : pos[a[i]]) {
            if (j <= i) continue;
            int len = j - i;
            if (j+len > n) break;
            if (get(i,i+len) == get(j,j+len)) {
                repeats.emplace_back(len,i);
                break;
            }
        }
    });

    ranges::sort(repeats);
    int cut = 0;
    for (auto [len, idx] : repeats) if (idx >= cut) cut = idx+len;

    cout << n-cut << "\n";
    #pragma acc parallel loop present(a)
    for (int i = cut; i < n; ++i) cout << b[a[i]] << " ";
    cout << "\n";
}
