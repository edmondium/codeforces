#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2e5+5;
int N,M,arr[maxn],pref[maxn][25],logg,st[4*maxn],stk;
int nor(int a,int b){
   return M^(a|b);
}
int getlog(int x){
   int ans=-1;
   while(x){
      ans+=1;
      x/=2;
   }
   return ans;
}
int internor(int l,int r){
   if(l<=0 or l>r)
      return 0;
   if(l==r)
      return arr[r];
   int ans=0;
   for(int j=0;j<=logg;j++){
      int bit=(1<<j);
      if(pref[r][j]<l)
         if((r-l+1)%2==1)
            bit=0;
      if(pref[r][j]==l)
         if((r-l+1)%2==0)
            bit=0;
      if(pref[r][j]>l)
         if((r-pref[r][j]+1)%2==1)
            bit=0;
      ans+=bit;
   }
   return ans;
}
void update(int lb,int rb,int x,int pos=1,int l=1,int r=stk){
   lb=max(1,lb);
   rb=min(N,rb);
   if(rb<lb)
      return;
   if(l==lb and r==rb){
      st[pos]=max(st[pos],x);
      return;
   }
   int mid=(l+r)/2;
   if(rb<=mid)
      return update(lb,rb,x,pos*2,l,mid);
   if(lb>mid)
      return update(lb,rb,x,pos*2+1,mid+1,r);
   update(lb,mid,x,pos*2,l,mid);
   update(mid+1,rb,x,pos*2+1,mid+1,r);
   return;
}
int get(int pos){
   pos+=stk-1;
   int v=0;
   while(pos){
      v=max(v,st[pos]);
      pos/=2;
   }
   return v;
}
void solve(){
   int K;
   cin>>N>>K;
   stk=1;
   while(stk<N)
      stk<<=1;
   M=(1<<K)-1;
   for(int i=1;i<=N;i++)
      cin>>arr[i];

   logg=getlog(M+1)-1;
   for(int i=1;i<=N;i++){
      for(int j=0;j<=logg;j++)
         if(arr[i]&(1<<j))
            pref[i][j]=i;
         else
            pref[i][j]=pref[i-1][j];
   }
   for(int i=1;i<=N;i++){
      for(int j=0;j<=logg;j++){
         int p=pref[i][j];
         for(int add=-2;add<=2;add++)
            update(p+add,i,internor(p+add,i));
      }
      update(1,i,internor(1,i));
   }
   for(int i=1;i<=N;i++)
      cout<<get(i)<<" \n"[i==N];
}
void reset(){
   for(int i=0;i<=N+2;i++){
      arr[i]=0;
      for(int j=0;j<=logg+2;j++)
         pref[i][j]=0;
   }
   logg=0;
   for(int i=0;i<=stk+stk;i++)
      st[i]=0;
}
int main(){
   int T=1;
   cin>>T;
   while(T--){
      solve();
      reset();
   }
   return 0;
}