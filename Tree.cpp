#include <bits/stdc++.h>
using namespace std;

struct bint {
    vector<int> a;
    bint(int x=0){a.clear();if(x==0){a.push_back(0);return;}while(x){a.push_back(x%10);x/=10;}}
    friend ostream& operator<<(ostream& os,const bint& b){for(int i=(int)b.a.size()-1;i>=0;i--)os<<b.a[i];return os;}
    bool operator<(const bint& o)const{if(a.size()!=o.a.size())return a.size()<o.a.size();for(int i=(int)a.size()-1;i>=0;i--)if(a[i]!=o.a[i])return a[i]<o.a[i];return false;}
    bint operator*(const bint& o)const{vector<int> t(a.size()+o.a.size());for(int i=0;i<(int)a.size();i++)for(int j=0;j<(int)o.a.size();j++)t[i+j]+=a[i]*o.a[j];int c=0;for(int i=0;i<(int)t.size()||c;i++){if(i==(int)t.size())t.push_back(0);c+=t[i];t[i]=c%10;c/=10;}while(t.size()>1&&t.back()==0)t.pop_back();bint r;r.a=t;return r;}
};

const int N=702;
vector<int> g[N];
bint dp[N][N+1];
int cnt[N];

auto dfs=[](auto&& self,int u,int p)->void{
    cnt[u]=1;
    dp[u][1]=bint(1);
    for(int v:g[u])if(v!=p){
        self(self,v,u);
        for(int sum=cnt[u]+cnt[v];sum>0;sum--){
            #pragma acc parallel loop
            for(int i=0;i<=cnt[v];i++){
                int j=sum-i;
                if(1<=j&&j<=cnt[u])dp[u][i+j]=max(dp[u][i+j],dp[u][j]*dp[v][i]);
            }
        }
        cnt[u]+=cnt[v];
    }
    for(int i=1;i<=cnt[u];i++)dp[u][0]=max(dp[u][0],dp[u][i]*bint(i));
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;cin>>n;
    for(int i=0;i<n;i++){g[i].clear();for(int j=0;j<=n;j++)dp[i][j]=bint();}
    for(int i=1;i<n;i++){int a,b;cin>>a>>b;--a;--b;g[a].push_back(b);g[b].push_back(a);}
    dfs(dfs,0,-1);
    cout<<dp[0][0]<<"\n";
}
