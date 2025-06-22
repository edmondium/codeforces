#include <bits/stdc++.h>

struct TwoSAT {
    int n;
    std::vector<std::vector<int>> adj, rev_adj;
    std::vector<bool> visited;
    std::vector<int> order, component;
    TwoSAT(int num_vars) : n(num_vars), adj(2 * n), rev_adj(2 * n), visited(2 * n), component(2 * n, -1) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }
    void add_clause(int u_lit, int v_lit) {
        auto lit_to_node = [&](int lit) {
            if (lit > 0) return lit - 1;
            return -lit - 1 + n;
        };
        int u_node = lit_to_node(u_lit);
        int v_node = lit_to_node(v_lit);
        int neg_u_node = lit_to_node(-u_lit);
        int neg_v_node = lit_to_node(-v_lit);
        add_edge(neg_u_node, v_node);
        add_edge(neg_v_node, u_node);
    }
    void dfs1(int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs1(v);
            }
        }
        order.push_back(u);
    }
    void dfs2(int u, int c) {
        component[u] = c;
        for (int v : rev_adj[u]) {
            if (component[v] == -1) {
                dfs2(v, c);
            }
        }
    }
    bool is_satisfiable() {
        std::fill(visited.begin(), visited.end(), false);
        order.clear();
        for (int i = 0; i < 2 * n; ++i) {
            if (!visited[i]) {
                dfs1(i);
            }
        }
        std::fill(component.begin(), component.end(), -1);
        int c = 0;
        std::reverse(order.begin(), order.end());
        for (int u : order) {
            if (component[u] == -1) {
                dfs2(u, c++);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (component[i] == component[i + n]) {
                return false;
            }
        }
        return true;
    }
};

using ull = unsigned long long;
struct Hashes {
    ull h1, h2;
    bool operator<(const Hashes& other) const {
        if (h1 != other.h1) return h1 < other.h1;
        return h2 < other.h2;
    }
    bool operator==(const Hashes& other) const {
        return h1 == other.h1 && h2 == other.h2;
    }
};

std::vector<ull> p1_pows, p2_pows;

void precompute_powers(int n) {
    if (!p1_pows.empty() && p1_pows.size() >= n + 1) return;
    ull P1 = 150001;
    ull P2 = 150007;
    p1_pows.resize(n + 1);
    p2_pows.resize(n + 1);
    p1_pows[0] = p2_pows[0] = 1;
    for (int i = 1; i <= n; ++i) {
        p1_pows[i] = p1_pows[i-1] * P1;
        p2_pows[i] = p2_pows[i-1] * P2;
    }
}

void solve() {
    int n, k;
    std::cin >> n >> k;
    TwoSAT solver(n);
    precompute_powers(n);
    for (int i = 0; i < k; ++i) {
        int m;
        std::cin >> m;
        std::vector<std::vector<int>> adj_list(n + 1);
        std::vector<std::vector<bool>> adj_matrix(n + 1, std::vector<bool>(n + 1, false));
        for (int j = 0; j < m; ++j) {
            int u, v;
            std::cin >> u >> v;
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
            adj_matrix[u][v] = adj_matrix[v][u] = true;
        }
        std::vector<std::pair<Hashes, int>> n_hashes;
        std::vector<std::pair<Hashes, int>> n_closed_hashes;
        for (int u = 1; u <= n; ++u) {
            Hashes h_n = {0, 0};
            for (int v : adj_list[u]) {
                h_n.h1 += p1_pows[v];
                h_n.h2 += p2_pows[v];
            }
            n_hashes.push_back({h_n, u});
            Hashes h_n_closed = h_n;
            h_n_closed.h1 += p1_pows[u];
            h_n_closed.h2 += p2_pows[u];
            n_closed_hashes.push_back({h_n_closed, u});
        }
        std::sort(n_hashes.begin(), n_hashes.end());
        std::sort(n_closed_hashes.begin(), n_closed_hashes.end());
        for (int u_idx = 0; u_idx < n; ) {
            int v_idx = u_idx;
            while (v_idx < n && n_hashes[v_idx].first == n_hashes[u_idx].first) {
                v_idx++;
            }
            for (int p1 = u_idx; p1 < v_idx; ++p1) {
                for (int p2 = p1 + 1; p2 < v_idx; ++p2) {
                    int u = n_hashes[p1].second;
                    int v = n_hashes[p2].second;
                    if (!adj_matrix[u][v]) {
                        solver.add_clause(u, v);
                    }
                }
            }
            u_idx = v_idx;
        }
        for (int u_idx = 0; u_idx < n; ) {
            int v_idx = u_idx;
            while (v_idx < n && n_closed_hashes[v_idx].first == n_closed_hashes[u_idx].first) {
                v_idx++;
            }
            for (int p1 = u_idx; p1 < v_idx; ++p1) {
                for (int p2 = p1 + 1; p2 < v_idx; ++p2) {
                    int u = n_closed_hashes[p1].second;
                    int v = n_closed_hashes[p2].second;
                    if (adj_matrix[u][v]) {
                        solver.add_clause(-u, -v);
                    }
                }
            }
            u_idx = v_idx;
        }
    }
    if (solver.is_satisfiable()) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
