#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2e5+5;
int n,a[maxn],p[maxn];
void construct(vector<int> pos,vector<int> nums,int layer){
   sort(nums.begin(),nums.end());
   if(pos.size()==1){
      p[pos[0]]=nums[0];
      return;
   }
   vector<int> keep,rem;
   vector<bool> spec;
   for(int x:pos)
      if(a[x]>layer){
         keep.push_back(x);
      }
   if(layer%2==1)
      reverse(nums.begin(),nums.end());
   vector<int> newnums;
   for(int it=1;it<=keep.size();it++){
      newnums.push_back(nums.back());
      nums.pop_back();
   }
   construct(keep,newnums,layer+1);
   reverse(nums.begin(),nums.end());
   int last;
   for(int x:pos){
      last=x;
      if(a[x]>layer)
         break;
      p[x]=nums.back();
      nums.pop_back();
   }
   reverse(nums.begin(),nums.end());
   for(int x:pos){
      if(x<last)
         continue;
      if(a[x]>layer)
         continue;
      p[x]=nums.back();
      nums.pop_back();
   }
}
void solve(){
   cin>>n;
   for(int i=1;i<=n;i++)
      cin>>a[i];
   for(int i=1;i<=n;i++)
      if(a[i]<=0)
         a[i]=1e9;
   vector<int> A;
   for(int i=1;i<=n;i++)
      A.push_back(i);
   construct(A,A,1);
   for(int i=1;i<=n;i++)
      cout<<p[i]<<" \n"[i==n];
}
int main(){
   int T;
   cin>>T;
   while(T--)
      solve();
}