#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
using ll = long long;

int n;
ll k;
array<int,55> s;
ll memo[55][2][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    ++k;
    s.fill(-1);
    s[0] = 0;

    function<ll(int,int,bool,bool)> solve = [&](int i,int j,bool tightRev,bool tightInvRev)->ll {
        if(i>j) return 1;
        if(memo[i][tightRev][tightInvRev]!=-1) return memo[i][tightRev][tightInvRev];
        ll res=0;
        #pragma omp parallel for reduction(+:res)
        for(int bi=0;bi<=1;++bi){
            if(s[i]!=-1 && s[i]!=bi) continue;
            for(int bj=0;bj<=1;++bj){
                if(i==j && bi!=bj) continue;
                if(s[j]!=-1 && s[j]!=bj) continue;
                if(tightRev && bi>bj) continue;
                if(tightInvRev && bi>(1-bj)) continue;
                res+=solve(i+1,j-1,tightRev&&(bi==bj),tightInvRev&&(bi==(1-bj)));
            }
        }
        return memo[i][tightRev][tightInvRev]=res;
    };

    auto count_valid = [&](){
        memset(memo,-1,sizeof(memo));
        return solve(0,n-1,true,true);
    };

    if(count_valid()<k){cout<<-1<<"\n";return 0;}
    for(int i=1;i<n;++i){
        s[i]=0;
        ll cnt=count_valid();
        if(cnt<k){k-=cnt;s[i]=1;}
    }
    for(int i=0;i<n;++i) cout<<s[i];
    cout<<"\n";
}
