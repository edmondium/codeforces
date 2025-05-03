#include <bits/stdc++.h>
using namespace std;
 
constexpr long long MOD = 1000000007;
 
// A DSU (union–find) structure.
struct DSU {
    vector<int> parent, size;
    DSU(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; i++) 
            parent[i] = i;
    }
    int find(int a) {
        return parent[a] = (a == parent[a] ? a : find(parent[a]));
    }
    void unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
};
 
// A coordinate on the grid.
struct Coord {
    int x, y;
    bool operator==(const Coord &other) const {
        return x == other.x && y == other.y;
    }
};
 
// Hash for Coord so we can use unordered_map/set.
struct CoordHash {
    size_t operator()(const Coord &c) const {
        return ((size_t)c.x) * 10007ull + (size_t)c.y;
    }
};
 
// An edge representing a segment’s constraint.
// If self==true, then it comes from a segment that had a unique query.
struct Edge {
    int u, v;
    bool self;
};
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;
        // There are k+1 preserved cells.
        vector<Coord> preserved(k+1);
        for (int i = 0; i <= k; i++){
            cin >> preserved[i].x >> preserved[i].y;
        }
 
        // Build a set of preserved (for quick filtering).
        unordered_set<Coord, CoordHash> preservedSet;
        preservedSet.reserve(k+1);
        for (const auto &p : preserved) {
            preservedSet.insert(p);
        }
 
        vector<Edge> edges;
        // We will assign an index to candidate cells.
        unordered_map<Coord, int, CoordHash> vertexMap;
        vector<Coord> vertices; // store candidate coordinates per vertex.
 
        // Helper lambda to get the vertex index for a candidate.
        auto getVertex = [&](const Coord &c) -> int {
            if (auto it = vertexMap.find(c); it != vertexMap.end())
                return it->second;
            int idx = vertices.size();
            vertices.push_back(c);
            vertexMap[c] = idx;
            return idx;
        };
 
        bool valid = true;
        // Process each segment (between consecutive preserved cells).
        for (int i = 0; i < k; i++){
            Coord a = preserved[i], b = preserved[i+1];
            int dx = abs(a.x - b.x), dy = abs(a.y - b.y);
            if(dx + dy != 2) {
                valid = false;
                break;
            }
            vector<Coord> cand;
            if(dx == 0 || dy == 0) {
                // Collinear: the only possibility is the midpoint.
                Coord mid { (a.x + b.x) / 2, (a.y + b.y) / 2 };
                cand.push_back(mid);
            } else {
                // Diagonal: the two possibilities
                cand.push_back({a.x, b.y});
                cand.push_back({b.x, a.y});
            }
 
            // Exclude a candidate if it is already one of the preserved cells.
            vector<Coord> allowed;
            for(auto &c : cand){
                if (preservedSet.find(c) == preservedSet.end())
                    allowed.push_back(c);
            }
 
            if(allowed.empty()){
                valid = false;
                break;
            }
 
            // If exactly one candidate remains, add a self-loop.
            if(allowed.size() == 1){
                int v = getVertex(allowed[0]);
                edges.push_back({v, v, true});
            } else { // Two allowed candidates.
                int u = getVertex(allowed[0]);
                int v = getVertex(allowed[1]);
                // They should be distinct; if not, it is a self-loop.
                if(u == v)
                    edges.push_back({u, u, true});
                else
                    edges.push_back({u, v, false});
            }
        }
 
        if(!valid){
            cout << 0 << "\n";
            continue;
        }
 
        int V = vertices.size();
        // Count forced (self-loop) usage for each vertex. A vertex used twice is forbidden.
        vector<int> selfLoopCount(V, 0);
        for (auto &e : edges) {
            if(e.self) {
                selfLoopCount[e.u]++;
                if(selfLoopCount[e.u] > 1) {
                    valid = false;
                    break;
                }
            }
        }
        if(!valid){
            cout << 0 << "\n";
            continue;
        }
 
        // Build a DSU (union–find) over vertices for non–self–loop edges.
        DSU dsu(V);
        for(auto &e : edges){
            if(!e.self) {
                dsu.unite(e.u, e.v);
            }
        }
 
        // Group vertices by component (using the DSU representative).
        vector<int> compSize(V, 0);
        for (int i = 0; i < V; i++){
            compSize[dsu.find(i)]++;
        }
 
        // Count the edges (each segment gives one edge) in each component.
        unordered_map<int, int> compEdges;
        // And record if any edge in the component is a self-loop.
        unordered_map<int, bool> compHasSelf;
        for(auto &e: edges){
            int comp = dsu.find(e.u);
            compEdges[comp] += 1;
            if(e.self)
                compHasSelf[comp] = true;
        }
 
        // Now, for each connected component the following holds (by the analysis):
        // • If e = s - 1 (a tree) then there are s ways.
        // • If e = s (a cycle) then if any self-loop is present then factor = 1, else factor = 2.
        // • Otherwise (e > s) the answer is 0.
        long long ans = 1;
        for (int i = 0; i < V; i++){
            if(dsu.find(i) != i) continue; // only consider representatives
            int s = compSize[i];
            int ecount = compEdges.count(i) ? compEdges[i] : 0;
            if(ecount == s - 1) {
                ans = (ans * s) % MOD;
            } else if(ecount == s) {
                if(compHasSelf.count(i) && compHasSelf[i])
                    ans = (ans * 1LL) % MOD;
                else
                    ans = (ans * 2LL) % MOD;
            } else {
                ans = 0;
                break;
            }
        }
 
        cout << ans % MOD << "\n";
    }
    return 0;
}
