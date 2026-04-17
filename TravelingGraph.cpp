#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll INF = 1e15;

static ll dist[16][16];
static int odd[16];
static ll dp[1<<15];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    vector deg(n,0);
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) dist[i][j]=(i==j?0:INF);

    ll sum=0;
    ranges::for_each(views::iota(0,m), [&](int){
        int x,y; ll w;
        cin >> x >> y >> w;
        --x;--y;
        dist[x][y]=min(dist[x][y],w);
        dist[y][x]=min(dist[y][x],w);
        sum+=w;
        (x==y ? deg[x]+=2 : (deg[x]++,deg[y]++));
    });

    for (int k=0;k<n;k++)
        for (int i=0;i<n;i++)
            for (int j=0;j<n;j++)
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);

    int sz=0;
    ranges::for_each(views::iota(0,n), [&](int i){ if(deg[i]%2) odd[sz++]=i; });

    fill(dp,dp+(1<<sz),INF);
    dp[0]=0;

    #pragma acc parallel loop copy(dp[0:(1<<sz)],dist,odd[0:sz])
    for (int mask=0;mask<(1<<sz);mask++) {
        if (dp[mask]==INF) continue;
        int i=0; while(i<sz && (mask>>i&1)) i++;
        if (i==sz) continue;
        for (int j=i+1;j<sz;j++) if(!(mask>>j&1)) {
            int nmask=mask|(1<<i)|(1<<j);
            dp[nmask]=min(dp[nmask],dp[mask]+dist[odd[i]][odd[j]]);
        }
    }

    ll ans=dp[(1<<sz)-1]+sum;
    bool reachable=ranges::all_of(views::iota(0,n), [&](int i){return deg[i]==0||dist[0][i]<INF;});
    cout<<(reachable?ans:-1)<<"\n";
}
