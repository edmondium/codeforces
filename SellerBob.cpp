#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    static constexpr int S = 1500;
    int d[S]{};
    void normalize() {
        int r=0;
        for(int i=0;i<S;i++){ d[i]+=r; r=d[i]/10; d[i]%=10; }
    }
    void output() const {
        int ft=S-1; while(ft>0 && d[ft]==0) ft--;
        for(int i=ft;i>=0;i--) cout<<d[i];
    }
};

BigInt operator+(const BigInt&a,const BigInt&b){
    BigInt c; for(int i=0;i<BigInt::S;i++) c.d[i]=a.d[i]+b.d[i];
    c.normalize(); return c;
}
BigInt operator*(const BigInt&a,int x){
    BigInt c; for(int i=0;i<BigInt::S;i++) c.d[i]=a.d[i]*x;
    c.normalize(); return c;
}
bool operator<(const BigInt&a,const BigInt&b){
    for(int i=BigInt::S-1;i>=0;i--) if(a.d[i]!=b.d[i]) return a.d[i]<b.d[i];
    return false;
}

static BigInt dp[5005], p2[2005];
static int pos[2005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; if(!(cin>>n)) return 0;
    memset(pos,-1,sizeof(pos));
    p2[0].d[0]=1;
    for(int i=0;i<2002;i++) p2[i+1]=p2[i]*2;
    #pragma acc parallel loop copy(dp[0:n+1],p2[0:2005],pos[0:2005])
    for(int i=0;i<n;i++){
        string s; int t; cin>>s>>t;
        dp[i+1]=dp[i];
        if(s=="win") pos[t]=i+1;
        else if(pos[t]!=-1){
            BigInt ndp=dp[pos[t]]+p2[t];
            if(dp[i+1]<ndp) dp[i+1]=ndp;
        }
    }
    dp[n].output();
}
