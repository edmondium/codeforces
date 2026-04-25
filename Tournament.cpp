#include <bits/stdc++.h>
#include <ranges>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    int m = n * (n - 1) / 2 - 1;
    vector<vector<int>> g(n + 1);
    vector<int> deg(n + 1);

    #pragma acc parallel loop
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        g[x].push_back(y);
        deg[x]++; deg[y]++;
    }

    auto cand = views::iota(1, n + 1)
              | views::filter([&](int i){ return deg[i] == n - 2; })
              | ranges::to<vector<int>>();

    auto reach = [&](int s, int t) {
        vector<int> vis(n + 1);
        function<void(int)> dfs = [&](int u) {
            vis[u] = 1;
            // #pragma acc parallel loop
            for (size_t i = 0; i < g[u].size(); i++) {
                int v = g[u][i];
                if (!vis[v]) dfs(v);
            }
        };
        dfs(s);
        return vis[t];
    };

    cout << (reach(cand[0], cand[1]) ? cand[0] : cand[1]) << " "
         << (reach(cand[0], cand[1]) ? cand[1] : cand[0]);
}
