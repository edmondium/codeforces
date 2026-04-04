#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

static constexpr array<pair<int,int>,8> dirs{{
    {0,1},{1,0},{0,-1},{-1,0},
    {1,1},{1,-1},{-1,1},{-1,-1}
}};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while(t--){
        int n,m; cin>>n>>m;
        vector<string> g(n); for(auto& r:g) cin>>r;
        int res=0;

        function<int(int,int)> floodFill=[&](int x,int y){
            if(x<0||x>=n||y<0||y>=m||g[x][y]!='1') return 0;
            g[x][y]='2';
            int cnt=1;
            for(auto [dx,dy]:dirs) cnt+=floodFill(x+dx,y+dy);
            return cnt;
        };

        auto checkFrame=[&](int x,int y,int d,int l,int r){
            for(int i=0;i<=d;i++){
                for(int j=l;j<r;j++){
                    auto [dx,dy]=dirs[j];
                    int xx=x+dx*i,yy=y+dy*i;
                    if(xx<0||xx>=n||yy<0||yy>=m||g[xx][yy]!='2') return false;
                }
            }
            return true;
        };

        #pragma omp parallel for reduction(+:res) schedule(dynamic)
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(g[i][j]=='1'){
            int s=floodFill(i,j);
            if(s%4) continue;
            int d=s/4;
            if(d==0||d>250) continue;
            if(checkFrame(i,j,d,0,2)&&checkFrame(i+d,j+d,d,2,4)) res++;
            if(checkFrame(i,j,d,4,6)&&checkFrame(i+2*d,j,d,6,8)) res++;
        }
        cout<<res<<"\n";
    }
}
