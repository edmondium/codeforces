#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using ull = unsigned long long;

#define X               first
#define Y               second
#define SZ(x)           int(x.size())
#define all(x)          x.begin(), x.end()
#define mins(a,b)       (a = min(a,b))
#define maxs(a,b)       (a = max(a,b))
#define pb              push_back
#define Mp              make_pair
#define lc              id<<1
#define rc              lc|1
#define mid             ((l+r)>>1)
mt19937_64              rng(chrono::steady_clock::now().time_since_epoch().count());

const ll  INF = 1e9 + 23;
const ll  MOD = 998244353;
const int MXN = 3006;
const int LOG = 23;

template<typename T>
inline T md(T x) { return x - (x>=MOD ? MOD : 0); }
template<typename T>
inline void fix(T &x) { x = md(x); }

int n;
vector<int> g[MXN];
vector<int> H[MXN];
int cnt[MXN], pscnt[MXN];
ll red[MXN], redb[MXN];
ll two[MXN], thr[MXN], itwo[MXN];
ll ans;
ll ps[MXN];

void dfs(int v, int h=0, int p=-1) {
    cnt[h]++;
    H[h].back()++;
    for(int u : g[v])
        if(u!=p)
            dfs(u, h+1, v);
}

void Main() {
    cin >> n;
    for(int i=1; i<=n; i++) g[i].clear();
    ans = 0;
    for(int i=0, u,v; i<n-1; i++) {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    for(int v=1; v<=n; v++) {
        for(int adj=-1; adj<SZ(g[v]); adj++) {
            for(int i=0; i<n; i++) H[i].clear(), cnt[i]=0;
            if(adj==-1) {
                cnt[0]++;
                for(int u : g[v]) {
                    for(int i=0; i<n; i++) H[i].pb(0);
                    dfs(u, 1, v);
                }
            }
            else {
                if(g[v][adj]<v) continue;
                for(int i=0; i<n; i++) H[i].pb(0);
                dfs(v, 0, g[v][adj]);
                for(int i=0; i<n; i++) H[i].pb(0);
                dfs(g[v][adj], 0, v);
            }
            pscnt[0] = cnt[0];
            for(int i=1; i<n; i++) pscnt[i] = pscnt[i-1] + cnt[i];
            red[0] = 1;
            redb[0] = 1;
            for(int i=1; i<n; i++) {
                red[i] = two[cnt[i]]-1;
                for(int a : H[i])
                    fix(red[i] += MOD-(two[a]-1));
                redb[i] = md(thr[cnt[i]]-two[cnt[i]]+MOD);
                for(int a : H[i])
                    fix(redb[i] += MOD-(thr[a]-two[a]+MOD)*two[cnt[i]-a]%MOD);
            }
            for(int i=0; i<n; i++) {
                ps[i] = red[i]*two[i==0?0:pscnt[i-1]]%MOD*(i+(adj!=-1))%MOD;
                if(i) fix(ps[i] += ps[i-1]);
            }
            for(int j=0; j<n; j++)
                fix(ans += thr[j==0?0:pscnt[j-1]]
                        *(thr[cnt[j]]-two[cnt[j]]+MOD)%MOD
                        *itwo[pscnt[j]]%MOD
                        *(ps[n-1]-ps[j]+MOD)%MOD);
            for(int i=0; i<n; i++) {
                ps[i] = red[i]*two[i==0?0:pscnt[i-1]]%MOD;
                if(i) fix(ps[i] += ps[i-1]);
            }
            for(int j=0; j<n; j++)
                fix(ans += thr[j==0?0:pscnt[j-1]]
                        *(thr[cnt[j]]-two[cnt[j]]+MOD)%MOD
                        *itwo[pscnt[j]]%MOD
                        *j%MOD
                        *(ps[n-1]-ps[j]+MOD)%MOD);
            for(int i=0; i<n; i++) {
                ps[i] = redb[i]
                        *thr[i==0?0:pscnt[i-1]]%MOD
                        *itwo[pscnt[i]]%MOD
                        *(i+(adj!=-1))%MOD;
                if(i) fix(ps[i] += ps[i-1]);
            }
            for(int j=1; j<n; j++)
                fix(ans += two[pscnt[j-1]]%MOD
                        *(two[cnt[j]]-1)%MOD
                        *ps[j-1]%MOD);
            for(int i=0; i<n; i++) {
                ps[i] = redb[i]
                        *thr[i==0?0:pscnt[i-1]]%MOD
                        *itwo[pscnt[i]]%MOD;
                if(i) fix(ps[i] += ps[i-1]);
            }
            for(int j=1; j<n; j++)
                fix(ans += two[pscnt[j-1]]%MOD
                        *(two[cnt[j]]-1)%MOD
                        *j%MOD
                        *ps[j-1]%MOD);
            for(int i=0; i<n; i++) {
                fix(ans += (redb[i]-red[i]+MOD)*thr[i==0?0:pscnt[i-1]]%MOD*(i+i+(adj!=-1))%MOD);
            }
        }
    }
    cout << ans << '\n';
}

int32_t main() {
    cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    two[0] = 1;
    for(int i=1; i<MXN; i++) two[i] = two[i-1]*2%MOD;
    thr[0] = 1;
    for(int i=1; i<MXN; i++) thr[i] = thr[i-1]*3%MOD;
    itwo[0] = 1;
    for(int i=1; i<MXN; i++) itwo[i] = itwo[i-1]*((MOD+1)/2)%MOD;
    while(T--) Main();
    return 0;
}