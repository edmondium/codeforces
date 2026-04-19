#include <bits/stdc++.h>
using namespace std;
using pii = pair<size_t,size_t>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t n, m, v;
    cin >> n >> m >> v;
    v--;
    if (m + 1 < n || m > 1 + (n - 1) * (n - 2) / 2) {
        cout << -1 << "\n";
        return 0;
    }
    size_t o = v == 0 ? 1 : 0;
    vector<pii> edges;
    edges.emplace_back(v+1, o+1);
    ranges::for_each(views::iota((size_t)0,n)
        | views::filter([&](size_t i){ return i!=v && i!=o; }),
        [&](size_t i){ edges.emplace_back(v+1,i+1); });
    m -= n - 1;
    for (size_t i=0; i<n && m; i++) {
        if (i==v || i==o) continue;
        for (size_t j=i+1; j<n && m; j++) {
            if (j==v || j==o) continue;
            edges.emplace_back(i+1,j+1);
            m--;
        }
    }
    #pragma acc parallel loop
    for (int i=0;i<(int)edges.size();i++)
        cout << edges[i].first << " " << edges[i].second << "\n";
}
