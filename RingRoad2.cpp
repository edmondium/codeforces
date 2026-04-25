#include <bits/stdc++.h>
using namespace std;

struct Edge { int a,b; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;
    cin >> n >> m;
    Edge* seg = new Edge[m];
    for (int i=0;i<m;i++) {
        int a,b; cin>>a>>b;
        if (a>b) swap(a,b);
        seg[i] = {a,b};
    }

    int* adj = new int[m*m]();

    auto cross = [&](Edge x, Edge y) {
        return (x.a < y.a && y.a < x.b && x.b < y.b) ||
               (y.a < x.a && x.a < y.b && y.b < x.b);
    };

    #pragma acc parallel loop collapse(2) copyin(seg[0:m]) copyout(adj[0:m*m])
    for (int i=0;i<m;i++)
        for (int j=0;j<m;j++)
            if (i<j) {
                if (cross(seg[i],seg[j])) {
                    adj[i*m+j]=1;
                    adj[j*m+i]=1;
                }
            }

    vector<int> color(m,-1);
    function<bool(int,int)> dfs=[&](int u,int c){
        color[u]=c;
        for(int v=0;v<m;v++) if(adj[u*m+v]) {
            if(color[v]==-1){
                if(!dfs(v,c^1)) return false;
            } else if(color[v]==c) return false;
        }
        return true;
    };
    for(int i=0;i<m;i++) if(color[i]==-1) if(!dfs(i,0)) {
        cout<<"Impossible\n";
        delete[] seg;
        delete[] adj;
        return 0;
    }
    for(int c:color) cout<<(c?'o':'i');
    cout<<"\n";

    delete[] seg;
    delete[] adj;
}
