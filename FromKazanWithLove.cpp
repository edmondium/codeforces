#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cassert>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    cout << fixed << setprecision(12);

    while (T--) {
        int n, m, x, y;
        cin >> n >> m >> x >> y;
        --x; --y;

        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u - 1].push_back(v - 1);
            adj[v - 1].push_back(u - 1);
        }

        // Read queries and record the paths
        vector<vector<int>> block;
        vector<int> temp_path;
        temp_path.reserve(n);

        auto dfs_find = [&](auto&& self, int u, int p, int target) -> bool {
            temp_path.push_back(u);
            if (u == target) return true;
            for (int v : adj[u]) {
                if (v == p) continue;
                if (self(self, v, u, target)) return true;
            }
            temp_path.pop_back();
            return false;
        };

        for (int qi = 0; qi < m; ++qi) {
            int a, b;
            cin >> a >> b;
            temp_path.clear();
            bool found = dfs_find(dfs_find, a - 1, -1, b - 1);
            assert(found);

            if (block.size() < temp_path.size())
                block.resize(temp_path.size());

            for (size_t i = 0; i < temp_path.size(); ++i) {
                block[i].push_back(temp_path[i]);
            }
        }

        vector<bool> active(n), current(n);
        vector<int> frontier{ x };
        vector<int> last_seen(n, -1);

        for (int t = 0; ; ++t) {
            if (t < static_cast<int>(block.size())) {
                for (int u : block[t]) current[u] = true;
            }

            vector<int> next_frontier;
            for (int u : frontier) {
                if (active[u] || current[u] || last_seen[u] == t) continue;
                last_seen[u] = t;
                bool has_active_neighbor = false;
                for (int v : adj[u]) {
                    if (active[v]) { has_active_neighbor = true; break; }
                }
                if (t > 0 && !has_active_neighbor) continue;
                next_frontier.push_back(u);
            }

            frontier.clear();
            if (t < static_cast<int>(block.size())) {
                for (int u : block[t]) {
                    current[u] = false;
                    if (active[u]) {
                        active[u] = false;
                    }
                    frontier.push_back(u);
                }
            }

            for (int u : next_frontier) {
                active[u] = true;
                for (int v : adj[u]) {
                    if (!active[v]) frontier.push_back(v);
                }
            }

            if (active[y]) {
                cout << (t + 1) << '\n';
                break;
            }

            if (t > static_cast<int>(block.size()) && frontier.empty()) {
                cout << -1 << '\n';
                break;
            }
        }
    }
    return 0;
}
