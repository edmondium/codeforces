#include<bits/stdc++.h>
 
using namespace std;
 
#define ll long long int
#define rep(i, n) for(ll i = 0; i < n;i++)
#define pb push_back

vector<vector<ll> > v;
 
bool EulerCycle(ll k)
{
    ll odd = 0, n=v.size();
    rep(i, n) if(v[i].size() % 2) odd++;
    
    
    if(odd == 0) return true;// G has all even degree vertices, so it has Euler Cycle
 
    rep(i, n)
    rep(j, v[i].size())
    if(v[v[i][j]].size()%2==v[i].size()%2){
        // cout<<i+1<<" "<<v[i][j]+1<<"\n";
        return false;
    }
 
    if(k>=2) return true;// L^2(G) has all even degree vertices, so it has Euler Cycle
 
    return false;
}
 
int LongestTrailingPath(ll n, ll p){
    if(v[n].size()>2) return 0;
    rep(i, v[n].size()) if(v[n][i]!=p) return 1+LongestTrailingPath(v[n][i], n);
    return 0;
}
 
void MarkVisited(ll n, vector<ll> &visited, vector<vector<ll> > &adj){
    visited[n]=1;
    rep(i, adj[n].size()){
        if(!visited[adj[n][i]]){
            MarkVisited(adj[n][i], visited, adj);
        }
    }
}
 
bool EulerPath(ll k){
    ll oddv[2], temp=0, n=v.size();
    rep(i, n) if(v[i].size()%2) oddv[temp++]=i;
    ll l[2]={LongestTrailingPath(oddv[0], -1), LongestTrailingPath(oddv[1], -1)};
    if(l[0]>l[1]) swap(l[0], l[1]), swap(oddv[0], oddv[1]);
    if(l[0]>=k) return true; // shortest longest trailing path is longer than k
    if(l[0]>0) return false; // shortest longest trailing path is non zero and less than k
    if(l[1]==1 && v[oddv[0]].size()==3 && v[oddv[1]][0] == oddv[0]) return true; // odd[0] and odd[1] are connected with one one have degree 1 and other having degree 3
    if(find(v[oddv[0]].begin(), v[oddv[0]].end(), oddv[1]) != v[oddv[0]].end()) return false; // odd[0] and odd[1] are adjacent
    if(k==1 || k>=3) return false; // Special cases left, and k=1, k>=4 don't satisfy it
 
    vector<vector<ll> > tempv(v);
    vector<ll> vis(v.size(), 0), noniso;
 
    rep(i, n){
        if(find(tempv[i].begin(), tempv[i].end(), oddv[0]) != tempv[i].end()) tempv[i].erase(find(tempv[i].begin(), tempv[i].end(), oddv[0]));
        if(find(tempv[i].begin(), tempv[i].end(), oddv[1]) != tempv[i].end()) tempv[i].erase(find(tempv[i].begin(), tempv[i].end(), oddv[1]));
        if(tempv[i].size()>0 && i!=oddv[0] && i!=oddv[1]) noniso.pb(i);
    }
 
    MarkVisited(noniso[0], vis, tempv);
    rep(i, noniso.size()){
        if(!vis[noniso[i]]) return false; // After removing odd degree vertices, there is more than one component
    }
 
    ll cntedge=0;
    rep(i, noniso.size()){
        int temp=0;
        if(find(v[noniso[i]].begin(), v[noniso[i]].end(), oddv[0]) != v[noniso[i]].end()) cntedge++, temp++;
        if(find(v[noniso[i]].begin(), v[noniso[i]].end(), oddv[1]) != v[noniso[i]].end()) cntedge++, temp++;
 
        if(temp && v[noniso[i]].size() > 2) return false; // Vertex connected to odd vertex has degree exactly 2
    }
    if(cntedge>2) return false; // More than 2 edges are connected to odd degree vertices from the component
 
    return true; // Special case, k=2 is always satisfied
}
 
void solve(){
    ll n, m, k;
    cin>>n>>m>>k;
 
    v.clear();
    v.resize(n);
 
    rep(i, m){
        ll x, y;
        cin>>x>>y;
        v[x-1].pb(y-1);
        v[y-1].pb(x-1);
    }
 
    if(EulerCycle(k)){
        cout<<"YES\n";
        return;
    }
    if(EulerPath(k)){
        cout<<"YES\n";
        return;
    }
    cout<<"NO\n";
}
 
int main()
{
    ll t;
    cin>>t;
 
    while(t--)
    {
        solve();
    }
}