#include <bits/stdc++.h>
#include <openacc.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<long long, vector<long long>> adj;
    for (int i = 0; i < n; ++i) {
        long long u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto start_node = (*ranges::find_if(adj, [](const auto& pair) {
        return pair.second.size() == 1;
    })).first;

    vector<long long> path(n + 1);
    path[0] = start_node;

    long long* path_ptr = path.data();
    
    auto get_next = [&](long long curr, long long p) {
        auto neighbors = adj[curr] | views::filter([&](long long v) { return v != p; });
        return *neighbors.begin();
    };

    path_ptr[1] = get_next(path_ptr[0], -1);
    
    #pragma acc data copy(path_ptr[0:n+1])
    {
        for (int i = 2; i <= n; ++i) {
            path_ptr[i] = get_next(path_ptr[i-1], path_ptr[i-2]);
        }
    }

    ranges::copy(path, ostream_iterator<long long>(cout, " "));
    cout << endl;

    return 0;
}