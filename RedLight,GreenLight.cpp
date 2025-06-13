#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n, k;
        cin >> n >> k;
        vector<ll> p(n+2);
        vector<int> d(n+2);
        for(int i=1; i<=n; i++){
            cin >> p[i];
        }
        p[0] = 0;            // left boundary (exit just before this)
        p[n+1] = (ll)1e15 + 1; 
        for(int i=1; i<=n; i++){
            cin >> d[i];
        }

        // f[i][dir][t] = -1 unvis, -2 visiting, 0 no, 1 yes
        static vector<array<vector<int>,2>> f; 
        f.resize(n+2);
        for(int i=0;i<=n+1;i++){
            f[i][0].assign(k, -1);
            f[i][1].assign(k, -1);
        }

        function<int(int,int,int)> dfs = [&](int i, int dir, int t)->int {
            int &res = f[i][dir==1][t];
            if(res != -1){
                if(res == -2) return res = 0;  // cycle ⇒ cannot exit
                return res;
            }
            res = -2;  // mark visiting

            // do you turn?
            if(t == d[i]) dir = -dir;

            int j = i + (dir==1 ? 1 : -1);
            if(j==0 || j==n+1){
                // stepping off the strip ⇒ exit
                return res = 1;
            }
            // distance to next light
            ll dist = llabs(p[j] - p[i]);
            int t2 = (t + dist % k) % k;
            return res = dfs(j, dir, t2);
        };

        // precompute on all real lights
        for(int i=1;i<=n;i++){
            for(int dir : {+1,-1}){
                for(int t=0;t<k;t++){
                    if(f[i][dir==1][t]==-1)
                        dfs(i, dir, t);
                }
            }
        }

        int q; 
        cin >> q;
        while(q--){
            ll a;
            cin >> a;
            // if beyond last light you immediately walk off
            if(a > p[n]){
                cout << "YES\n";
                continue;
            }
            // find first light >= a
            int i = int(lower_bound(p.begin()+1, p.begin()+n+1, a) - p.begin());
            ll dist0 = p[i] - a;
            int t0 = int(dist0 % k);
            // arriving at light i at time t0, dir=+1
            cout << (f[i][1][t0] == 1 ? "YES\n" : "NO\n");
        }
    }
    return 0;
}
