#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<std::vector<int>> g(n + 1);
    for (int i : std::views::iota(0, n - 1)) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto is_leaf = [&](int i) { return i > 1 && g[i].size() == 1; };
    auto leaves_view = std::views::iota(2, n + 1) | std::views::filter(is_leaf);
    std::vector<int> leaves(leaves_view.begin(), leaves_view.end());

    std::vector<int> order(leaves.size());
    for (int& x : order) std::cin >> x;

    std::vector<int> dist( (n + 1) * (n + 1), 1e9);
    std::vector<int> parent( (n + 1) * (n + 1), -1);

    auto idx = [n](int i, int j) { return i * (n + 1) + j; };

    for (int i : std::views::iota(1, n + 1)) {
        dist[idx(i, i)] = 0;
        for (int v : g[i]) {
            dist[idx(i, v)] = 1;
            parent[idx(i, v)] = i;
        }
    }

    int* d_ptr = dist.data();
    int* p_ptr = parent.data();

    #pragma acc parallel loop copy(d_ptr[0:dist.size()], p_ptr[0:parent.size()])
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int ik = i * (n + 1) + k;
                int kj = k * (n + 1) + j;
                int ij = i * (n + 1) + j;
                if (d_ptr[ik] + d_ptr[kj] < d_ptr[ij]) {
                    d_ptr[ij] = d_ptr[ik] + d_ptr[kj];
                    p_ptr[ij] = p_ptr[kj];
                }
            }
        }
    }

    auto get_path = [&](int u, int v) {
        std::vector<int> p;
        while (v != u && v != -1) {
            p.push_back(v);
            v = parent[idx(u, v)];
        }
        p.push_back(u);
        std::ranges::reverse(p);
        return p;
    };

    std::vector<int> res{1};
    for (int target : order) {
        auto p = get_path(res.back(), target);
        res.insert(res.end(), p.begin() + 1, p.end());
    }
    
    auto back = get_path(res.back(), 1);
    res.insert(res.end(), back.begin() + 1, back.end());

    if (res.size() != 2 * n - 1) {
        std::cout << -1 << std::endl;
    } else {
        std::ranges::for_each(res, [](int x) { std::cout << x << " "; });
        std::cout << std::endl;
    }

    return 0;
}