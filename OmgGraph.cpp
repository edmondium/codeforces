#include <bits/stdc++.h>
using namespace std;
 
// ----------------------
// DSU for MST construction
// ----------------------
struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int a) {
        return parent[a] == a ? a : parent[a] = find(parent[a]);
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false;
        if(rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if(rank[a] == rank[b])
            rank[a]++;
        return true;
    }
};
 
// ----------------------
// Edge structure
// ----------------------
struct Edge {
    int u, v;
    long long w;
};
 
// ----------------------
// LCA for maximum edge queries on MST
// ----------------------
 
int LOG; // maximum power
vector<vector<int>> up;           // up[k][v] is the 2^k-th ancestor of v
vector<vector<long long>> maxEdgeUp;  // maxEdgeUp[k][v] is maximum edge weight from v to its 2^k-th ancestor
vector<int> depth;
 
void dfs(int v, int p, long long w, const vector<vector<pair<int,long long>>>& tree) {
    up[0][v] = p;
    maxEdgeUp[0][v] = (p == -1 ? 0 : w);
    for(auto &edge : tree[v]) {
        int to = edge.first;
        long long wt = edge.second;
        if(to == p) continue;
        depth[to] = depth[v] + 1;
        dfs(to, v, wt, tree);
    }
}
 
// Preprocess the MST tree for LCA queries.
void preprocessLCA(int n, int root, const vector<vector<pair<int,long long>>>& tree) {
    LOG = 32 - __builtin_clz(n);
    up.assign(LOG, vector<int>(n, -1));
    maxEdgeUp.assign(LOG, vector<long long>(n, 0));
    depth.assign(n, 0);
    dfs(root, -1, 0, tree);
    for (int k = 1; k < LOG; k++) {
        for (int v = 0; v < n; v++) {
            if (up[k-1][v] != -1) {
                up[k][v] = up[k-1][up[k-1][v]];
                maxEdgeUp[k][v] = max(maxEdgeUp[k-1][v], maxEdgeUp[k-1][up[k-1][v]]);
            } else {
                up[k][v] = -1;
                maxEdgeUp[k][v] = maxEdgeUp[k-1][v];
            }
        }
    }
}
 
// Query the maximum edge weight on the path between u and v in the MST.
long long queryMax(int u, int v) {
    if (u == -1 || v == -1) return 0;
    long long ans = 0;
    if (depth[u] < depth[v])
        swap(u,v);
    // Bring u up to same level as v.
    int d = depth[u] - depth[v];
    for (int k = 0; k < LOG; k++) {
        if(d & (1 << k)) {
            ans = max(ans, maxEdgeUp[k][u]);
            u = up[k][u];
        }
    }
    if(u == v) return ans;
    for (int k = LOG-1; k >= 0; k--) {
        if(up[k][u] != up[k][v]) {
            ans = max(ans, max(maxEdgeUp[k][u], maxEdgeUp[k][v]));
            u = up[k][u];
            v = up[k][v];
        }
    }
    ans = max(ans, max(maxEdgeUp[0][u], maxEdgeUp[0][v]));
    return ans;
}
 
// ----------------------
// Main
// ----------------------
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<Edge> edges(m);
        for (int i = 0; i < m; i++){
            int u, v;
            long long w;
            cin >> u >> v >> w;
            u--; v--; // switch to 0-indexed
            edges[i] = {u, v, w};
        }
 
        // Build MST with Kruskal
        vector<Edge> mstEdges;  // will store MST edges
        DSU dsu(n);
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b){
            return a.w < b.w;
        });
        // We'll build the MST tree (adjacency list):
        vector<vector<pair<int, long long>>> tree(n);
        for(auto &e : edges){
            if(dsu.unite(e.u, e.v)){
                mstEdges.push_back(e);
                tree[e.u].push_back({e.v, e.w});
                tree[e.v].push_back({e.u, e.w});
            }
        }
 
        // (Graph is connected, so MST has n-1 edges.)
        // Preprocess LCA on the MST. (Use vertex 0 as root.)
        preprocessLCA(n, 0, tree);
 
        // For each forced edge, compute a candidate path cost.
        // Candidate = L + min( max(L, query(1->u), query(v->n) ),
        //                        max(L, query(1->v), query(u->n) ) )
        // Note: vertices are 0-indexed; so 1 becomes 0 and n becomes n-1.
        long long ans = LLONG_MAX;
        for(auto &e : edges) {
            long long L = e.w;
            // Option 1: force e on the path as (1->u) + e + (v->n)
            long long max1 = max({L, queryMax(0, e.u), queryMax(e.v, n-1)});
            // Option 2: force e as (1->v) + e + (u->n)
            long long max2 = max({L, queryMax(0, e.v), queryMax(e.u, n-1)});
            long long candidate = L + min(max1, max2);
            ans = min(ans, candidate);
        }
 
        cout << ans << "\n";
    }
 
    return 0;
}
