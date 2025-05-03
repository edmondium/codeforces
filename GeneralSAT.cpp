#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> size;
    int maxSize;

    DSU(int n) : parent(n), size(n, 1), maxSize(1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int a) {
        return (parent[a] == a) ? a : parent[a] = find(parent[a]);
    }

    void unionSet(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        if (size[a] > maxSize)
            maxSize = size[a];
    }
};

struct Edge {
    int u, v;
    int w;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++){
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        // convert 1-indexed vertices to 0-indexed
        edges[i].u--;
        edges[i].v--;
    }
    
    // sort edges by weight ascending
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });
    
    // Store queries: each query is a pair (k, original index)
    vector<pair<int,int>> queries(q);
    for (int i = 0; i < q; i++){
        int k;
        cin >> k;
        queries[i] = {k, i};
    }
    // sort queries by k value ascending
    sort(queries.begin(), queries.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.first < b.first;
    });
    
    DSU dsu(n);
    vector<int> answer(q, 0);
    int edgeIndex = 0;
    
    // Process each query in increasing order of k
    for (int i = 0; i < q; i++){
        int k = queries[i].first;
        // Process all edges with weight <= current query k
        while (edgeIndex < m && edges[edgeIndex].w <= k) {
            dsu.unionSet(edges[edgeIndex].u, edges[edgeIndex].v);
            edgeIndex++;
        }
        // answer is the maximum connected component size at this moment.
        answer[queries[i].second] = dsu.maxSize;
    }
    
    // Print answers in original order.
    for (int a : answer)
        cout << a << "\n";
    
    return 0;
}
