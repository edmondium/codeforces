#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> danger(n + 1);
        for (int i = 1; i <= n; i++){
            cin >> danger[i];
        }
        
        // Build the undirected tree.
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i < n; i++){
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
 
        // For each vertex v:
        // M[v] = maximum prefix sum (i.e. threat value) in its vertical path.
        // m[v] = minimum prefix sum in its vertical path.
        vector<ll> Mval(n + 1, 0), mval(n + 1, 0);
 
        // DFS from the root (vertex 1).
        function<void(int, int)> dfs = [&](int u, int par) {
            if (par == 0) {
                // For the root.
                Mval[u] = danger[u];
                mval[u] = danger[u];
            } else {
                // For a non-root vertex:
                // X(u) = { danger[u] } ∪ { danger[u] - x for every x in X(par) }
                // Thus, 
                //   M(u) = max( danger[u], danger[u] - m(par) )
                //   m(u) = min( danger[u], danger[u] - M(par) )
                Mval[u] = max(danger[u], danger[u] - mval[par]);
                mval[u] = min(danger[u], danger[u] - Mval[par]);
            }
            for (int v : adj[u]) {
                if (v != par) {
                    dfs(v, u);
                }
            }
        };
        dfs(1, 0);
 
        // Output the threat value (M(v)) for every vertex from 1 to n.
        for (int i = 1; i <= n; i++){
            cout << Mval[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
