#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> f(n);
    std::vector<int> in_degree(n, 0);

    for (int i = 0; i < n; ++i) {
        std::cin >> f[i];
        f[i]--;
    }

    int* f_ptr = f.data();
    int* in_ptr = in_degree.data();

    #pragma acc parallel loop copyin(f_ptr[0:n]) copyout(in_ptr[0:n])
    for (int i = 0; i < n; ++i) {
        #pragma acc atomic update
        in_ptr[f_ptr[i]]++;
    }

    std::vector<bool> visited(n, false);
    std::vector<std::pair<int, int>> paths;

    auto trace = [&](int start) {
        int curr = start;
        while (!visited[curr]) {
            visited[curr] = true;
            curr = f[curr];
        }
        return curr;
    };

    auto zero_deg_nodes = std::views::iota(0, n) 
                        | std::views::filter([&](int i) { return in_degree[i] == 0; });

    std::ranges::for_each(zero_deg_nodes, [&](int i) {
        paths.push_back({i + 1, trace(i) + 1});
    });

    auto unvisited_nodes = std::views::iota(0, n) 
                         | std::views::filter([&](int i) { return !visited[i]; });

    std::ranges::for_each(unvisited_nodes, [&](int i) {
        paths.push_back({i + 1, trace(i) + 1});
    });

    if (paths.size() == 1) {
        bool all_one = std::ranges::all_of(in_degree, [](int d) { return d > 0; });
        if (all_one) {
            std::cout << 0 << std::endl;
            return 0;
        }
    }

    std::cout << paths.size() << "\n";
    
    auto indices = std::views::iota(0, (int)paths.size());
    std::ranges::for_each(indices, [&](int i) {
        std::cout << paths[i].second << " " << paths[(i + 1) % paths.size()].first << "\n";
    });

    return 0;
}