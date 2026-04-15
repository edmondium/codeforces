#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

struct Edge { int idx,u,v; int other(int x) const { return x==u?v:u; } };

const int MAXN=10005, MAXM=10005;
Edge E[MAXM];
vector<Edge*> adj[MAXN];
int color[MAXN],depth[MAXN];
Edge* parent[MAXN];
pii bb[MAXN];
int sum_bad=0;
Edge* one_bad=nullptr;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;cin>>n>>m;
    for(int i=0;i<m;i++){int u,v;cin>>u>>v;--u;--v;E[i]={i+1,u,v};adj[u].push_back(&E[i]);adj[v].push_back(&E[i]);}
    fill(color,color+n,-1);
    auto dfs=[&](auto&& self,int i,Edge* p,int c,int d)->void{
        parent[i]=p;color[i]=c;depth[i]=d;int bad=0,ok=0;
        for(auto e:adj[i]) if(e!=p){
            int j=e->other(i);
            if(color[j]==-1){self(self,j,e,c^1,d+1);bad+=bb[j].first;ok+=bb[j].second;}
            else if(depth[j]>depth[i]) (color[j]==color[i]? --bad : --ok);
            else {if(color[j]==color[i]){++bad;one_bad=e;++sum_bad;} else ++ok;}
        }
        bb[i]={bad,ok};
    };
    #pragma acc parallel loop copyin(E[0:m]) copy(color[0:n],depth[0:n],parent[0:n],bb[0:n])
    for(int i=0;i<n;i++) if(color[i]==-1) dfs(dfs,i,nullptr,0,0);
    if(sum_bad==0){cout<<m<<"\n";for(int i=0;i<m;i++) cout<<E[i].idx<<(i+1==m?'\n':' ');}
    else {set<int> ret;if(sum_bad==1) ret.insert(one_bad->idx);
        for(int i=0;i<n;i++){if(!parent[i]) continue;if(bb[i].first==sum_bad && bb[i].second==0) ret.insert(parent[i]->idx);}
        cout<<ret.size()<<"\n";for(auto it=ret.begin();it!=ret.end();++it) cout<<*it<<(next(it)==ret.end()?'\n':' ');}
}
