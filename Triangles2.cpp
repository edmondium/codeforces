#include <bits/stdc++.h>
using namespace std;

static constexpr int64_t MOD = 1'000'000'009;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n;
    cin >> n;

    // special case
    if (n == 2) {
        cout << 10 << "\n";
        return 0;
    }

    // zb[i] = (3 + 2*zb[i-1]) % MOD
    vector<int64_t> zb(n + 1);
    zb[0] = 1;
    for (int i = 1; i <= n; ++i) {
        zb[i] = (3 + 2 * zb[i - 1]) % MOD;
    }

    // build ans exactly like your original loop
    int64_t ans = 0;
    int64_t cur = 1;
    for (int64_t fd = 3; fd <= n; ++fd) {
        if (fd & 1) {
            int64_t idx = ((fd - 1) >> 1) - 1;
            if (idx >= 0)
                cur = cur * zb[idx] % MOD;
        }
        ans = (ans + 2 * cur) % MOD;
    }

    // final magic formula
    ans = (
        (2 * (((ans + 2) % MOD) * ans % MOD)) % MOD
      + (ans * 4) % MOD
      + 10
    ) % MOD;

    cout << ans << "\n";
    return 0;
}
