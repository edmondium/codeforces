#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = (ll)1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // e[i][j] = min edge weight from i→j (INF if none)
    // d[i][j] = shortest-path distance from i→j
    vector<vector<ll>> e(n, vector<ll>(n, INF));
    vector<vector<ll>> d(n, vector<ll>(n, INF));

    // no self-loops
    for(int i = 0; i < n; i++){
        e[i][i] = 0;
    }

    // read edges, but we swap x,y to model y→x
    for(int i = 0; i < m; i++){
        int x, y;
        ll w;
        cin >> x >> y >> w;
        --x; --y;
        swap(x, y);
        e[x][y] = min(e[x][y], w);
    }

    // floyd–warshall initialization
    d = e;
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            if (d[i][k] == INF) continue;
            for(int j = 0; j < n; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    int q;
    cin >> q;
    while(q--){
        ll op;
        cin >> op;
        vector<ll> a(n);
        for(ll& x : a) 
            cin >> x;

        // min_dist[k] = min over all j of (a[j] + d[j][k])
        // min_one_edge[k] = min over all j of (a[j] + e[j][k])
        vector<ll> min_dist = a;
        vector<ll> min_one_edge = a;
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                min_dist[k]       = min(min_dist[k],       a[j] + d[j][k]);
                min_one_edge[k]   = min(min_one_edge[k],   a[j] + e[j][k]);
            }
        }

        // min_op[k] = minimum total “–1”s needed to force instability at k
        vector<ll> min_op(n, INF);
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                // only if the shortest path from j→k uses more than one edge
                if(d[j][k] < e[j][k]){
                    ll best_val  = d[j][k] + a[j];
                    ll alt_bound = min_one_edge[k] - 1;
                    min_op[k] = min(min_op[k], best_val - alt_bound);
                }
            }
        }

        string ans(n, '0');
        for(int i = 0; i < n; i++){
            if(min_op[i] <= op) 
                ans[i] = '1';
        }
        cout << ans << '\n';
    }

    return 0;
}
