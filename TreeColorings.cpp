#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

inline constexpr int M   = 500'000;
inline constexpr int INF = 1'000'000'000;

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // allocate and init
    std::vector dp(M + 1, INF);
    dp[1] = 1;

    // precompute dp[2..M]
    for (int m = 2; m <= M; ++m) {
        int root = static_cast<int>(std::sqrt(m));
        for (int i = 1; i <= root; ++i) {
            if (m % i != 0) continue;
            int a = i, b = m / i;
            if (b > 2) dp[m] = std::min(dp[m], dp[a] + dp[b - 2]);
            if (a > 2) dp[m] = std::min(dp[m], dp[b] + dp[a - 2]);
        }
    }

    int q;
    std::cin >> q;
    while (q--) {
        int m;
        std::cin >> m;
        std::cout << (dp[m] == INF ? -1 : dp[m]) << '\n';
    }

    return 0;
}
