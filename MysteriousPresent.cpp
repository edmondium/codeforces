#include <bits/stdc++.h>
#include <ranges>
#include <omp.h>
using namespace std;

struct Envelope { int w, h, idx; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, cardW, cardH;
    cin >> n >> cardW >> cardH;

    vector<Envelope> envelopes;
    envelopes.reserve(n);

    for (int i = 0; i < n; ++i) {
        int w, h;
        cin >> w >> h;
        if (w > cardW && h > cardH) envelopes.push_back({w, h, i + 1});
    }

    if (envelopes.empty()) {
        cout << 0 << '\n';
        return 0;
    }

    ranges::sort(envelopes, [](auto &a, auto &b) {
        return a.w == b.w ? a.h > b.h : a.w < b.w;
    });

    int m = (int)envelopes.size();
    vector<int> dp(m, 1), parent(m, -1);

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
            if (envelopes[i].w > envelopes[j].w && envelopes[i].h > envelopes[j].h) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }
    }

    int bestIndex = ranges::max_element(
        views::iota(0, m),
        {},
        [&](int i){ return dp[i]; }
    ) - views::iota(0, m).begin();

    vector<int> chain;
    for (int i = bestIndex; i != -1; i = parent[i]) chain.push_back(envelopes[i].idx);
    ranges::reverse(chain);

    cout << chain.size() << '\n';
    for (int i = 0; i < (int)chain.size(); ++i)
        cout << chain[i] << (i + 1 == (int)chain.size() ? '\n' : ' ');
}
