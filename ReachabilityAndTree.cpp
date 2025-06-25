#include <bits/stdc++.h>
#include <ranges>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> g(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        // 1) find a vertex of degree 2
        int root = -1;
        for (int i = 0; i < n; i++) {
            if (g[i].size() == 2) {
                root = i;
                break;
            }
        }
        if (root < 0) {
            cout << "NO\n";
            continue;
        }

        // 2) prepare for DFS
        vector<char> used(n, 0);
        vector<pair<int,int>> ans;
        ans.reserve(n - 1);

        // 3) lambda-based DFS that flips orientation each step
        auto dfs = [&](auto&& self, int v, bool flip) -> void {
            used[v] = 1;
            for (int to : g[v]) {
                if (used[to]) 
                    continue;
                if (flip) 
                    ans.emplace_back(to, v);
                else 
                    ans.emplace_back(v, to);
                self(self, to, !flip);
            }
        };

        // 4) seed the two edges out of the degree-2 root
        int u = g[root][0], v = g[root][1];
        ans.emplace_back(root, u);
        ans.emplace_back(v, root);
        used[root] = 1;

        // 5) grow two alternating‐orientation trees
        dfs(dfs, u, true);
        dfs(dfs, v, false);

        // 6) output
        cout << "YES\n";
        ranges::sort(ans);
        for (auto [a, b] : ans)
            cout << a + 1 << ' ' << b + 1 << "\n";
    }
    return 0;
}
