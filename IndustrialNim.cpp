#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;

auto prefix_xor = [](u64 t) {
    switch (t & 3ULL) {
        case 0: return t;
        case 1: return 1ULL;
        case 2: return t + 1ULL;
        default: return 0ULL;
    }
};

auto range_xor = [](u64 l, u64 r) {
    return (l > r) ? 0ULL : (prefix_xor(r) ^ prefix_xor(l - 1));
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<u64,u64>> quarries(n);
    for (auto& [x,m] : quarries) cin >> x >> m;

    u64 total_nim = 0;
    #pragma acc parallel loop reduction(^:total_nim)
    for (int i = 0; i < n; i++) {
        total_nim ^= range_xor(quarries[i].first, quarries[i].first + quarries[i].second - 1);
    }

    cout << (total_nim ? "tolik\n" : "bolik\n");
}
