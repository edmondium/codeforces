#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> g(n+1);
    for (int i=0;i<m;i++) {
        int a,b,w;
        cin >> a >> b >> w;
        g[a].emplace_back(b,w);
        g[b].emplace_back(a,w);
    }
    vector<long long> dist(n+1,LLONG_MAX);
    vector<int> parent(n+1,-1);
    dist[1]=0;
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<>> pq;
    pq.emplace(0,1);
    while(!pq.empty()) {
        auto [d,u]=pq.top(); pq.pop();
        if(d!=dist[u]) continue;
        #pragma acc parallel loop
        for(int i=0;i<(int)g[u].size();i++) {
            auto [v,w]=g[u][i];
            if(dist[v]>d+w) {
                dist[v]=d+w;
                parent[v]=u;
                pq.emplace(dist[v],v);
            }
        }
    }
    if(dist[n]==LLONG_MAX) {
        cout << -1;
        return 0;
    }
    vector<int> path;
    for(int v=n;v!=-1;v=parent[v]) path.push_back(v);
    reverse(path.begin(),path.end());
    for(auto x:path) cout<<x<<" ";
}
