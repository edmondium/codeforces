#include <bits/stdc++.h>
using namespace std;
static constexpr int64_t MOD = 1'000'000'009;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64_t n;
    cin >> n;
    if (n == 2) {
        cout << 10 << "\n";
        return 0;
    }

    int64_t* zb = new int64_t[n+1];
    zb[0] = 1;

    #pragma acc parallel loop copy(zb[0:n+1])
    for (int i = 1; i <= n; ++i)
        zb[i] = (3 + 2 * zb[i - 1]) % MOD;

    int64_t cur = 1;
    auto seq = views::iota(int64_t(3), n + 1);

    int64_t ans = ranges::fold_left(seq, int64_t(0),
        [&](int64_t acc, int64_t fd) {
            if (fd & 1) {
                int64_t idx = ((fd - 1) >> 1) - 1;
                if (idx >= 0) cur = cur * zb[idx] % MOD;
            }
            return (acc + 2 * cur) % MOD;
        });

    ans = (
        (2 * (((ans + 2) % MOD) * ans % MOD)) % MOD
      + (ans * 4) % MOD
      + 10
    ) % MOD;

    cout << ans << "\n";
    delete[] zb;
}
