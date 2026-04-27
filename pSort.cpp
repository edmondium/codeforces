#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> p(n), d(n);
    for (auto &x : p) cin >> x, --x;
    for (auto &x : d) cin >> x;

    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        int a = i - d[i], b = i + d[i];
        if (a >= 0) g[i].push_back(a), g[a].push_back(i);
        if (b < n) g[i].push_back(b), g[b].push_back(i);
    }

    vector<int> vis(n);
    auto dfs = [&](auto self, int u, vector<int>& comp)->void {
        vis[u] = 1;
        comp.push_back(u);
        for (int v : g[u]) if (!vis[v]) self(self, v, comp);
    };

    for (int i = 0; i < n; ++i) if (!vis[i]) {
        vector<int> comp;
        dfs(dfs, i, comp);

        vector<int> a = comp, b(comp.size());
        int cs = comp.size();
        int* pp = p.data();
        int* cc = comp.data();
        int* bb = b.data();

        #pragma acc parallel loop copyin(pp[0:n], cc[0:cs]) copyout(bb[0:cs])
        for (int k = 0; k < cs; ++k) bb[k] = pp[cc[k]];

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        if (a != b) {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";
}
