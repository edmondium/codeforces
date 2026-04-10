#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge { int u,v; ll w; };

ll edmonds(int n,int root,vector<Edge>& edges){
    const ll INF=LLONG_MAX/4;
    ll res=0;
    while(true){
        vector<ll> in(n,INF);
        vector<int> pre(n,-1);
        #pragma acc parallel loop
        for(int i=0;i<(int)edges.size();i++){
            auto&e=edges[i];
            if(e.u!=e.v && e.w<in[e.v]){ in[e.v]=e.w; pre[e.v]=e.u; }
        }
        in[root]=0;
        if(any_of(in.begin(),in.end(),[&](ll x){return x==INF;})) return -1;
        res=accumulate(in.begin(),in.end(),res);
        int cnt=0;
        vector<int> id(n,-1),vis(n,-1);
        for(int i=0;i<n;i++){
            int v=i;
            while(vis[v]!=i && id[v]==-1 && v!=root){ vis[v]=i; v=pre[v]; }
            if(v!=root && id[v]==-1){
                for(int u=pre[v];u!=v;u=pre[u]) id[u]=cnt;
                id[v]=cnt++;
            }
        }
        if(cnt==0) break;
        for(int i=0;i<n;i++) if(id[i]==-1) id[i]=cnt++;
        vector<Edge> ne;
        ne.reserve(edges.size());
        #pragma acc parallel loop
        for(int i=0;i<(int)edges.size();i++){
            auto&e=edges[i];
            int u=id[e.u],v=id[e.v];
            ll w=e.w;
            if(u!=v) w-=in[e.v];
            ne.push_back({u,v,w});
        }
        n=cnt; root=id[root]; edges=move(ne);
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin>>n;
    vector<ll> q(n);
    for(auto&x:q) cin>>x;
    int m; cin>>m;
    vector<Edge> edges;
    edges.reserve(m);
    for(int i=0;i<m;i++){ int a,b; ll c; cin>>a>>b>>c; --a;--b; if(q[a]>q[b]) edges.push_back({a,b,c}); }
    ll maxq=*max_element(q.begin(),q.end());
    vector<int> roots; for(int i=0;i<n;i++) if(q[i]==maxq) roots.push_back(i);
    if(roots.size()!=1){ cout<<-1<<"\n"; return 0; }
    ll ans=edmonds(n,roots[0],edges);
    cout<<ans<<"\n";
}
