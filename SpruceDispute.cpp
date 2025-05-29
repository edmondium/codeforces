#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

// Global variables. (They are reinitialized in each test case.)
ll n; 
vector<vector<ll>> g;  // graph (0-indexed)
vector<ll> coloring;   // color assigned to each vertex

ll centroid;       // candidate centroid vertex
ll best;           // a leaf (with minimal DFS distance) to pick the removal edge
ll best_dist;      // its DFS distance (used to pick the closest leaf)
ll colorCounter;   // counter used while DFS‐coloring

// DFS that returns the subtree size of node u;
// it finds a centroid (a vertex u for which every subtree size and the "complement" are at most n/2).
ll search_centroid(ll u, ll parent) {
    ll sum = 0;
    bool isCentroid = true;
    for (ll v : g[u]) {
        if (v == parent)
            continue;
        ll subtreeSize = search_centroid(v, u);
        if (subtreeSize > n / 2)
            isCentroid = false;
        sum += subtreeSize;
    }
    // The complement is n - (sum + 1)
    if (isCentroid && (n - (sum + 1)) <= n / 2)
        centroid = u;
    return sum + 1;
}

// DFS that assigns colors (in cyclic order).
// Also it records a leaf (a vertex with only one adjacent vertex, and not the root) with minimal depth.
void make_coloring(ll u, ll parent, ll dist) {
    // assign a color in round‐robin order (colors: 1 .. (n/2))
    coloring[u] = (colorCounter++ % (n / 2)) + 1;
    // if u is a leaf — note that for a non-root, leaf means degree == 1
    if (parent != -1 && g[u].size() == 1) {
        if (dist < best_dist) {
            best_dist = dist;
            best = u;
        }
    }
    for (ll v : g[u]) {
        if (v == parent)
            continue;
        make_coloring(v, u, dist + 1);
    }
}
    
// Main routine for one test case.
void solve() {
    cin >> n;
    // Initialize structures.
    g.assign(n, vector<ll>());
    coloring.assign(n, 0);
    colorCounter = 0;
    centroid = -1;
    best_dist = 200005;  // big initial value
    best = -1;
    
    // Read tree (edges; vertices are given 1-indexed, so convert to 0-indexed)
    for (ll i = 0; i < n - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    // Start the centroid search from a “random” vertex (here chosen as 1543 % n)
    ll start = 1543 % n;
    search_centroid(start, -1);
    
    // Now color the tree starting from the centroid.
    make_coloring(centroid, -1, 0);
    
    // Choose the removal edge.
    // best is a leaf; since it is a leaf it has exactly one neighbor.
    ll neigh = g[best].front();
    // We want to print the edge with the smaller vertex first.
    // Let the removal vertex be the larger one among best and neigh.
    ll removed = max(best, neigh);
    ll parent_vertex = min(best, neigh);
    
    // To “fix” the extra occurrence of a color (since the DFS coloring assigns colors to all n vertices),
    // we assign the removed vertex’s color to the centroid and then set the removed vertex’s color to 0.
    coloring[centroid] = coloring[removed];
    coloring[removed] = 0;
    
    // Output: first the edge (in 1-indexed, with a < b) and then the colors for each vertex.
    cout << (parent_vertex + 1) << " " << (removed + 1) << "\n";
    for (ll i = 0; i < n; i++) {
        cout << coloring[i] << (i + 1 == n ? "\n" : " ");
    }
}
    
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
