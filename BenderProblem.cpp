#include <bits/stdc++.h>
#include <ranges>
using namespace std;
using PII = pair<int,int>;

struct Nail { int x,y; };

int dist(const Nail& a,const Nail& b){
    return abs(a.x-b.x)+abs(a.y-b.y);
}

vector<int> compute_needs(const vector<Nail>& nails){
    int n=nails.size();
    vector<int> need(n);
    #pragma acc parallel loop
    for(int i=0;i<n;i++){
        need[i]=dist(nails[i],nails[(i+1)%n])+dist(nails[i],nails[(i+n-1)%n]);
    }
    return need;
}

vector<int> attempt(int sh,const vector<int>& need,set<PII> rods,int n){
    vector<int> res(n,-1);
    for(int ii=0;ii<n/2;ii++){
        int i=(ii*2+sh)%n;
        int len=need[i];
        auto it=rods.lower_bound({len,-1});
        if(it==rods.end()||it->first!=len) return {};
        res[i]=it->second+1;
        rods.erase(it);
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; cin>>n>>m;
    vector<Nail> nails(n);
    for(auto& p:nails) cin>>p.x>>p.y;
    set<PII> rods;
    for(int i=0;i<m;i++){int x;cin>>x;rods.insert({x,i});}
    auto need=compute_needs(nails);
    auto r1=attempt(0,need,rods,n);
    auto r2=attempt(1,need,rods,n);
    if(!r1.empty()){cout<<"YES\n";for(int i=0;i<n;i++)cout<<(i?" ":"")<<r1[i];}
    else if(!r2.empty()){cout<<"YES\n";for(int i=0;i<n;i++)cout<<(i?" ":"")<<r2[i];}
    else cout<<"NO\n";
}
