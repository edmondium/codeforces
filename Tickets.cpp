#include <bits/stdc++.h>
using namespace std;
using ld = long double;

auto main() -> int {
    int n, m, k;
    cin >> n >> m >> k;
    auto seq_num = views::iota(0, k+1)
                 | views::transform([&](int i){ return (ld)(m - i); });
    auto seq_den = views::iota(0, k+1)
                 | views::transform([&](int i){ return (ld)(n + i + 1); });
    auto prod = [](auto rng){ return accumulate(rng.begin(), rng.end(), (ld)1, multiplies<>()); };
    auto prob = [&]() -> ld {
        if (m <= k) return 1.0L;
        ld val = 1.0L - prod(seq_num) / prod(seq_den);
        return clamp(val, 0.0L, 1.0L);
    };
    ld ans;
    #pragma acc parallel copyin(n,m,k) copyout(ans)
    {
        ans = prob();
    }
    cout << fixed << setprecision(6) << ans << endl;
}
