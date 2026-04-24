#include <bits/stdc++.h>
#include <ranges>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m,n,A,B,C;
    cin>>m>>n>>A>>B>>C;
    int mm=m,nn=n;
    if((m&1)&&(n&1)){cout<<"IMPOSSIBLE\n";return 0;}
    vector<vector<char>> ans(mm+1,vector<char>(nn+1));
    if(m&1){
        ranges::for_each(views::iota(1,n+1),[&](int i){ans[m][i]='a'+((i+1)&2)/2;});
        m--; A-=n/2;
    }
    if(n&1){
        ranges::for_each(views::iota(1,m+1),[&](int i){ans[i][n]='c'+((i+1)&2)/2;});
        n--; B-=m/2;
    }
    auto fill=[&](int i,int j,char a,char b,char c,char d){
        ans[i*2-1][j*2-1]=a; ans[i*2][j*2-1]=b;
        ans[i*2-1][j*2]=c; ans[i*2][j*2]=d;
    };
    bool fail=false;
    #pragma acc parallel loop collapse(2) reduction(|:fail)
    for(int i=1;i<=m/2;i++) for(int j=1;j<=n/2;j++){
        if(C>0){
            C--; char ch=(i+j)&1?'f':'e'; fill(i,j,ch,ch,ch,ch);
        } else if(B>1){
            B-=2; char g=(i+j)&1?'h':'g',h=(i+j)&1?'j':'i'; fill(i,j,g,g,h,h);
        } else if(A>1){
            A-=2; char k=(i+j)&1?'l':'k',mch=(i+j)&1?'n':'m'; fill(i,j,k,mch,k,mch);
        } else fail=true;
    }
    if(fail||A<0||B<0||C<0){cout<<"IMPOSSIBLE\n";return 0;}
    ranges::for_each(views::iota(1,mm+1),[&](int i){
        ranges::for_each(views::iota(1,nn+1),[&](int j){cout<<ans[i][j];});
        cout<<"\n";
    });
}
