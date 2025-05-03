#include <bits/stdc++.h>
using namespace std;

// Dinic max-flow with integer capacities
struct Edge {
    int to, rev;
    long long cap;
};
struct Dinic {
    int N;
    vector<vector<Edge>> G;
    vector<int> level, prog;
    Dinic(int N): N(N), G(N), level(N), prog(N) {}
    void addEdge(int u, int v, long long c) {
        G[u].push_back({v, (int)G[v].size(), c});
        G[v].push_back({u, (int)G[u].size()-1, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s]=0; q.push(s);
        while(!q.empty()) {
            int u=q.front(); q.pop();
            for(auto &e: G[u]) {
                if(level[e.to]<0 && e.cap>0) {
                    level[e.to]=level[u]+1;
                    q.push(e.to);
                }
            }
        }
        return level[t]>=0;
    }
    long long dfs(int u, int t, long long f) {
        if(u==t) return f;
        for(int &i=prog[u]; i<(int)G[u].size(); ++i) {
            Edge &e=G[u][i];
            if(e.cap>0 && level[e.to]==level[u]+1) {
                long long ret = dfs(e.to, t, min(f, e.cap));
                if(ret>0) {
                    e.cap-=ret;
                    G[e.to][e.rev].cap+=ret;
                    return ret;
                }
            }
        }
        return 0;
    }
    long long maxFlow(int s, int t) {
        long long flow=0, inf=LLONG_MAX;
        while(bfs(s,t)) {
            fill(prog.begin(), prog.end(), 0);
            while(true) {
                long long f=dfs(s,t,inf);
                if(!f) break;
                flow+=f;
            }
        }
        return flow;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int>a(n), w(n);
    for(int i=0;i<n;i++) cin >> a[i];
    long long Wtot=0;
    for(int i=0;i<n;i++){
        cin >> w[i];
        Wtot += w[i];
    }
    // 1) compute dp1, dp2
    vector<int> dp1(n,1), dp2(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++)
            if(a[j]<a[i])
                dp1[i]=max(dp1[i], dp1[j]+1);
    }
    for(int i=n-1;i>=0;i--){
        for(int j=n-1;j>i;j--)
            if(a[j]>a[i])
                dp2[i]=max(dp2[i], dp2[j]+1);
    }
    int L = *max_element(dp1.begin(), dp1.end());

    // collect critical vertices V
    vector<int> idx; // will hold original indices
    for(int i=0;i<n;i++){
        if(dp1[i] + dp2[i] - 1 == L)
            idx.push_back(i);
    }
    int m = idx.size();
    // build flow graph:
    // nodes: for each critical i: in=0..m-1, out=m..2m-1. plus S=2m, T=2m+1
    int S = 2*m, T = 2*m + 1;
    Dinic D(2*m + 2);
    const long long INF = LLONG_MAX/4;

    // add vertex‐splitting edges
    for(int k=0;k<m;k++){
        int i = idx[k];
        D.addEdge(k, k+m, w[i]);
    }
    // add the “LIS‐step” edges
    for(int k=0;k<m;k++){
        for(int l=0;l<m;l++){
            int i = idx[k], j = idx[l];
            if(i<j && a[i]<a[j] && dp1[j]==dp1[i]+1){
                D.addEdge(k+m, l, INF);
            }
        }
    }
    // source to all dp1==1, sink from all dp1==L
    for(int k=0;k<m;k++){
        int i = idx[k];
        if(dp1[i]==1)   D.addEdge(S,   k,   INF);
        if(dp1[i]==L)   D.addEdge(k+m, T,   INF);
    }

    long long flow = D.maxFlow(S,T);
    // answer = total weights - min deletion weight
    cout << (Wtot - flow) << endl;
    return 0;
}
