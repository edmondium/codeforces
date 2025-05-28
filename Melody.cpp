#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <stack>
#include <algorithm>
using namespace std;
 
// This solution uses the observation that each sound (volume, pitch)
// can be seen as an edge connecting a vertex for volume and a vertex for pitch.
// An Eulerian trail in this bipartite graph produces an ordering of sounds (edges)
// such that consecutive edges share a vertex. Since the graph is bipartite, the
// shared vertex alternates between volume and pitch, exactly as required.
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<pair<int,int>> sounds(n);
        for (int i = 0; i < n; i++){
            int v, p;
            cin >> v >> p;
            sounds[i] = {v, p};
        }
 
        // Map volumes (left side) and pitches (right side) to separate vertex indices.
        unordered_map<int, int> volMap, pitchMap;
        volMap.reserve(n * 2);
        pitchMap.reserve(n * 2);
        int volCount = 0, pitchCount = 0;
 
        for (int i = 0; i < n; i++){
            int v = sounds[i].first;
            if(volMap.find(v) == volMap.end()){
                volMap[v] = volCount++;
            }
        }
 
        for (int i = 0; i < n; i++){
            int p = sounds[i].second;
            if(pitchMap.find(p) == pitchMap.end()){
                pitchMap[p] = pitchCount++;
            }
        }
 
        int V = volCount + pitchCount; // total vertices
        // Build the undirected bipartite graph:
        // - Left vertices: indices [0, volCount-1] for volumes.
        // - Right vertices: indices [volCount, V-1] for pitches.
        // Each sound i becomes an edge between volMap[sounds[i].first] and (volCount + pitchMap[sounds[i].second]).
        vector<vector<pair<int, int>>> graph(V);
        for (int i = 0; i < n; i++){
            int volId = volMap[sounds[i].first];
            int pitchId = volCount + pitchMap[sounds[i].second];
            graph[volId].push_back({pitchId, i});
            graph[pitchId].push_back({volId, i});
        }
 
        // Check connectivity (for vertices that are incident to at least one edge).
        int startVertex = -1;
        for (int i = 0; i < V; i++){
            if (!graph[i].empty()){
                startVertex = i;
                break;
            }
        }
 
        if(startVertex == -1){
            // Should not happen since n >= 1.
            cout << "NO\n";
            continue;
        }
 
        vector<bool> visited(V, false);
        function<void(int)> dfs = [&](int u) {
            visited[u] = true;
            for(auto &edge : graph[u]) {
                int v = edge.first;
                if (!visited[v])
                    dfs(v);
            }
        };
        dfs(startVertex);
        bool connected = true;
        for (int i = 0; i < V; i++){
            if (!graph[i].empty() && !visited[i]) {
                connected = false;
                break;
            }
        }
 
        if(!connected){
            cout << "NO\n";
            continue;
        }
 
        // Check the Eulerian trail condition: the number of vertices with odd degree should be 0 or 2.
        int oddCount = 0, oddVertex = -1;
        for (int i = 0; i < V; i++){
            if (!graph[i].empty() && (graph[i].size() % 2 == 1)) {
                oddCount++;
                oddVertex = i;
            }
        }
        if(oddCount != 0 && oddCount != 2) {
            cout << "NO\n";
            continue;
        }
 
        // Pick a starting vertex:
        // If there are 2 odd vertices, start at one of them; else start at the vertex we found earlier.
        int start = (oddCount == 2 ? oddVertex : startVertex);
 
        // Now find an Eulerian trail using Hierholzer’s algorithm.
        // We will output the order of edges (sounds) as they appear in the Eulerian trail.
        vector<bool> used(n, false);  // For each edge/sound.
        vector<int> order;            // To store the edge IDs in the order they are used.
 
        // The stack will store pairs: (current_vertex, edge id through which we arrived at this vertex).
        // For the start vertex, we use -1 for the edge id.
        vector<pair<int, int>> st;
        st.push_back({start, -1});
 
        while(!st.empty()){
            int u = st.back().first;
            if(!graph[u].empty()){
                auto [v, eid] = graph[u].back();
                graph[u].pop_back();
                if(used[eid])
                    continue;
                used[eid] = true;
                st.push_back({v, eid});
            } else {
                auto [u, eid] = st.back();
                st.pop_back();
                if(eid != -1)
                    order.push_back(eid);
            }
        }
 
        if(order.size() != (size_t)n) {
            cout << "NO\n";
            continue;
        }
 
        // The order is produced in reverse, so reverse it.
        reverse(order.begin(), order.end());
 
        // Output the answer.
        // (Our edge IDs are 0-indexed; add 1 to each to obtain the 1-indexed sound indices.)
        cout << "YES\n";
        for (int i = 0; i < n; i++){
            cout << order[i] + 1 << (i + 1 < n ? " " : "\n");
        }
    }
 
    return 0;
}
