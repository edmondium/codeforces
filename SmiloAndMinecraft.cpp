#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using ll = long long;

static constexpr int MAXN = 500;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        int n, m, k;
        std::cin >> n >> m >> k;
        --k; // convert to 0-based radius

        std::vector<std::string> mine(n);
        ll total_gold = 0;
        for (auto &row : mine) {
            std::cin >> row;
            total_gold += std::count(row.begin(), row.end(), 'g');
        }

        // build 2D prefix sum: dimensions (n+1)x(m+1)
        std::vector<std::vector<int>> pref(n + 1, std::vector<int>(m + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                pref[i+1][j+1] = pref[i+1][j] + pref[i][j+1]
                                 - pref[i][j] + (mine[i][j] == 'g');
            }
        }

        // helper to clamp indices into [0, limit]
        auto clamp_idx = [](int x, int lim) {
            return std::clamp(x, 0, lim);
        };

        ll min_block = total_gold;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mine[i][j] == '.') {
                    int a = clamp_idx(i - k, n);
                    int b = clamp_idx(i + k + 1, n);
                    int c = clamp_idx(j - k, m);
                    int d = clamp_idx(j + k + 1, m);

                    // sum in rectangle [a,b) x [c,d)
                    ll gold_block = pref[b][d] - pref[a][d]
                                   - pref[b][c] + pref[a][c];
                    min_block = std::min(min_block, gold_block);
                }
            }
        }

        std::cout << (total_gold - min_block) << '\n';
    }
    return 0;
}
