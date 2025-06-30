#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;

// XOR of [0..t]
u64 prefix_xor(u64 t) {
    switch (t & 3ULL) {
        case 0: return t;
        case 1: return 1;
        case 2: return t + 1;
        default: return 0;
    }
}

// XOR of [l..r]
u64 range_xor(u64 l, u64 r) {
    if (l > r) return 0;
    return prefix_xor(r) ^ prefix_xor(l - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    u64 total_nim = 0;
    for (int i = 0; i < n; i++) {
        u64 x, m;
        cin >> x >> m;
        total_nim ^= range_xor(x, x + m - 1);
    }

    cout << (total_nim ? "tolik\n" : "bolik\n");
    return 0;
}
