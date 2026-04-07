#include <bits/stdc++.h>
using namespace std;

static int parentArr[205];
static bool inPath[205], compVis[205];
static int distArr[205], dist2Arr[205];
static int q1[205], q2[205];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0,a,b;i<n-1;i++){
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    long long answer = 0;
    vector<int> path;

    #pragma acc parallel loop collapse(2) reduction(max:answer)
    for(int u=0; u<n; u++){
        for(int v=0; v<n; v++){
            if(v <= u) continue;

            for(int i=0;i<n;i++) parentArr[i] = -1;
            int h=0,t=0;
            parentArr[u] = u;
            q1[t++] = u;

            while(h<t && parentArr[v] == -1){
                int x = q1[h++];
                for(int y : adj[x]){
                    if(parentArr[y] == -1){
                        parentArr[y] = x;
                        q1[t++] = y;
                    }
                }
            }

            path.clear();
            int cur = v;
            while(parentArr[cur] != cur){
                path.push_back(cur);
                cur = parentArr[cur];
            }
            path.push_back(u);
            int pathLen = (int)path.size() - 1;

            for(int i=0;i<n;i++){
                inPath[i] = false;
                compVis[i] = false;
            }
            for(int x : path) inPath[x] = true;

            int bestDiam = 0;

            for(int i=0;i<n;i++){
                if(inPath[i] || compVis[i]) continue;

                int hh=0,tt=0;
                q1[tt++] = i;
                compVis[i] = true;
                distArr[i] = 0;
                vector<int> comp;
                comp.push_back(i);
                int far = i;

                while(hh<tt){
                    int x = q1[hh++];
                    if(distArr[x] > distArr[far]) far = x;
                    for(int y : adj[x]){
                        if(!inPath[y] && !compVis[y]){
                            compVis[y] = true;
                            distArr[y] = distArr[x] + 1;
                            q1[tt++] = y;
                            comp.push_back(y);
                        }
                    }
                }

                for(int x : comp) dist2Arr[x] = -1;

                hh=0; tt=0;
                dist2Arr[far] = 0;
                q2[tt++] = far;
                int diam = 0;

                while(hh<tt){
                    int x = q2[hh++];
                    diam = max(diam, dist2Arr[x]);
                    for(int y : adj[x]){
                        if(!inPath[y] && dist2Arr[y] == -1){
                            dist2Arr[y] = dist2Arr[x] + 1;
                            q2[tt++] = y;
                        }
                    }
                }

                if(diam > bestDiam) bestDiam = diam;
            }

            long long val = 1LL * pathLen * bestDiam;
            if(val > answer) answer = val;
        }
    }

    cout << answer << "\n";
    return 0;
}
