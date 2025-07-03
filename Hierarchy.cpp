#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> q(n+1);
    for(int i = 1; i <= n; i++) cin >> q[i];

    int m;
    cin >> m;
    struct Edge { int a, b; ll c; };
    vector<Edge> edges(m);
    for(int i = 0; i < m; i++){
        cin >> edges[i].a >> edges[i].b >> edges[i].c;
    }

    // 1) Find root candidates
    ll max_q = *max_element(q.begin()+1, q.end());
    vector<int> roots;
    for(int i = 1; i <= n; i++){
        if(q[i] == max_q) roots.push_back(i);
    }
    if(roots.size() != 1) {
        cout << -1 << "\n";
        return 0;
    }
    int root = roots[0];

    // 2) Track minimum incoming cost for each node
    const ll INF = LLONG_MAX/4;
    vector<ll> min_in(n+1, INF);
    min_in[root] = 0;  // root has no supervisor cost

    for(auto &e : edges) {
        // qualification constraint guaranteed by input
        if(e.c < min_in[e.b]) {
            min_in[e.b] = e.c;
        }
    }

    // 3) Compute total cost and check connectivity
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(min_in[i] == INF) {
            cout << -1 << "\n";
            return 0;
        }
        ans += min_in[i];
    }

    cout << ans << "\n";
    return 0;
}
