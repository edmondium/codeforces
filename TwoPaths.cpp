#include <bits/stdc++.h>
using namespace std;

static int n;
static vector<int> adj[200];
static int parentArr[200];
static bool inPath[200], compVis[200];
static int distArr[200], dist2Arr[200];
static int q[200], q2[200];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0; i < n; i++) adj[i].clear();
    for(int i = 0, a, b; i < n-1; i++){
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    long long answer = 0;
    vector<int> path;

    // For every pair of endpoints u < v
    for(int u = 0; u < n; u++){
        for(int v = u + 1; v < n; v++){
            // 1) BFS from u until v to fill parentArr[]
            for(int i = 0; i < n; i++) parentArr[i] = -1;
            int qh = 0, qt = 0;
            parentArr[u] = u;
            q[qt++] = u;
            while(qh < qt && parentArr[v] == -1){
                int x = q[ qh++ ];
                for(int y: adj[x]){
                    if(parentArr[y] == -1){
                        parentArr[y] = x;
                        q[qt++] = y;
                    }
                }
            }

            // 2) Reconstruct the unique path u->...->v
            path.clear();
            int cur = v;
            while(parentArr[cur] != cur){
                path.push_back(cur);
                cur = parentArr[cur];
            }
            path.push_back(u);
            int pathLen = int(path.size()) - 1;

            // 3) Mark those vertices removed
            for(int i = 0; i < n; i++){
                inPath[i] = false;
                compVis[i] = false;
            }
            for(int x: path) inPath[x] = true;

            // 4) On the remaining forest compute the maximum diameter
            int bestDiam = 0;
            for(int i = 0; i < n; i++){
                if(inPath[i] || compVis[i]) continue;

                // BFS1: collect one component starting at i, find farthest 'far'
                int head = 0, tail = 0;
                q[tail++] = i;
                compVis[i] = true;
                distArr[i] = 0;
                vector<int> compNodes;
                compNodes.push_back(i);
                int far = i;

                while(head < tail){
                    int x = q[head++];
                    if(distArr[x] > distArr[far]) far = x;
                    for(int y: adj[x]){
                        if(!inPath[y] && !compVis[y]){
                            compVis[y] = true;
                            distArr[y] = distArr[x] + 1;
                            q[tail++] = y;
                            compNodes.push_back(y);
                        }
                    }
                }

                // BFS2: from 'far' compute this component's diameter
                // reset dist2Arr only on the nodes we will visit
                for(int x: compNodes) dist2Arr[x] = -1;

                int hh = 0, tt = 0;
                dist2Arr[far] = 0;
                q2[tt++] = far;
                int diam = 0;

                while(hh < tt){
                    int x = q2[hh++];
                    diam = max(diam, dist2Arr[x]);
                    for(int y: adj[x]){
                        if(!inPath[y] && dist2Arr[y] == -1){
                            dist2Arr[y] = dist2Arr[x] + 1;
                            q2[tt++] = y;
                        }
                    }
                }

                bestDiam = max(bestDiam, diam);
            }

            // 5) maximize the product
            answer = max(answer, 1LL * pathLen * bestDiam);
        }
    }

    cout << answer << "\n";
    return 0;
}
