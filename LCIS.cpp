#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    cin >> m;
    vector<int> b(m);
    for (auto &x : b) cin >> x;

    vector<int> dp(m), parent(m, -1);

    for (int i = 0; i < n; ++i) {
        int current_length = 0, last_idx = -1;
        #pragma omp parallel for
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                #pragma omp critical
                {
                    if (current_length + 1 > dp[j]) {
                        dp[j] = current_length + 1;
                        parent[j] = last_idx;
                    }
                }
            }
            if (a[i] > b[j]) {
                #pragma omp critical
                {
                    if (dp[j] > current_length) {
                        current_length = dp[j];
                        last_idx = j;
                    }
                }
            }
        }
    }

    auto best = ranges::max_element(dp | views::enumerate,
        [](auto const &p1, auto const &p2) {
            return get<1>(p1) < get<1>(p2);
        });

    int end_idx = get<0>(*best);
    int max_len = get<1>(*best);

    cout << max_len << "\n";

    if (max_len > 0) {
        vector<int> result;
        for (int idx = end_idx; idx != -1; idx = parent[idx])
            result.push_back(b[idx]);
        ranges::reverse(result);
        for (int i = 0; i < (int)result.size(); ++i)
            cout << result[i] << (i + 1 == (int)result.size() ? "" : " ");
        cout << "\n";
    }
}
