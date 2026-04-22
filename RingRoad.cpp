#include <bits/stdc++.h>
using namespace std;

struct Edge { int to,c; };

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin>>n;
    vector<vector<Edge>> adj(n+1);
    int total=0;
    for(int i=0;i<n;i++){
        int u,v,c;cin>>u>>v>>c;
        adj[u].push_back({v,0});
        adj[v].push_back({u,c});
        total+=c;
    }
    vector<int> path;
    int cur=1,prev=-1;
    for(int i=0;i<n;i++){
        auto it=find_if(adj[cur].begin(),adj[cur].end(),[&](auto&e){return e.to!=prev;});
        path.push_back(it->c);
        prev=cur;cur=it->to;
    }
    int path_cost=0;
    #pragma acc parallel loop reduction(+:path_cost)
    for(int i=0;i<n;i++) path_cost+=path[i];
    cout<<min(path_cost,total-path_cost)<<"\n";
}
