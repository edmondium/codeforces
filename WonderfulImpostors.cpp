#include <bits/stdc++.h>
using namespace std;

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<tuple<int, int, int>> statements(m);
        for (auto &[tp, a, b] : statements)
            cin >> tp >> a >> b;

        int q;
        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            vector<int> mark(n + 3, 0);

            // Only apply type-0 statements in [l, r]
            for (int i = l-1; i <= r-1; ++i) {
                auto [tp, a, b] = statements[i];
                if (tp == 0) {
                    mark[a]++;
                    mark[b+1]--;
                }
            }

            vector<int> zero(n + 2, 0);
            for (int i = 1; i <= n; ++i) {
                mark[i] += mark[i-1];
                zero[i] = (mark[i] > 0 ? 1 : 0);
            }

            vector<int> prefix(n + 2, 0);
            for (int i = 1; i <= n; ++i)
                prefix[i] = prefix[i-1] + zero[i];

            bool ok = true;
            for (int i = l-1; i <= r-1; ++i) {
                auto [tp, a, b] = statements[i];
                if (tp == 1) {
                    int total = b - a + 1;
                    int cnt_zero = prefix[b] - prefix[a-1];
                    if (cnt_zero == total) {
                        ok = false;
                        break;
                    }
                }
            }
            cout << (ok ? "YES\n" : "NO\n");
        }
    }
}

int main() {
    solve();
}
