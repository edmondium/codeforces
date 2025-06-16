#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int merge(const std::vector<int>& a, const std::vector<int>& b) {
    int n = int(a.size()), res = 0;
    int i = 0, j = 0;
    for (int c = 0; c < n; ++c) {
        if (a[i] > b[j]) {
            ++res;
            ++i;
        } else {
            ++j;
        }
    }
    return res;
}

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (auto& x : a) std::cin >> x;
    for (auto& x : b) std::cin >> x;

    // pref_min[i] = index of the smallest element in a[0..i]
    std::vector<int> pref_min(n);
    pref_min[0] = 0;
    for (int i = 1; i < n; ++i) {
        pref_min[i] = (a[i] < a[pref_min[i-1]] ? i : pref_min[i-1]);
    }

    // suf_max[i] = index of the largest element in a[i..n-1]
    std::vector<int> suf_max(n);
    suf_max[n-1] = n-1;
    for (int i = n-2; i >= 0; --i) {
        suf_max[i] = (a[i] > a[suf_max[i+1]] ? i : suf_max[i+1]);
    }

    // baseline without swaps
    int low = merge(a, b), high = n;

    // can we reach ≥m wins by exactly one swap?
    auto can = [&](int m) {
        int x = pref_min[m-1];
        int y = suf_max[m];
        std::swap(a[x], a[y]);
        bool ok = merge(a, b) >= m;
        std::swap(a[x], a[y]);
        return ok;
    };

    // binary-search the maximum achievable
    while (high - low > 1) {
        int mid = (low + high) >> 1;
        if (can(mid)) {
            low = mid;
        } else {
            high = mid;
        }
    }

    std::cout << low << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
