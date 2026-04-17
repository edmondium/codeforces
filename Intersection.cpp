#include <bits/stdc++.h>
using namespace std;

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a1,b1,c1,a2,b2,c2;
    cin>>a1>>b1>>c1>>a2>>b2>>c2;
    int ans;
    #pragma acc parallel loop
    for(int i=0;i<1;i++){
        if(a1==0 && b1==0 && c1!=0) ans=0;
        else if(a2==0 && b2==0 && c2!=0) ans=0;
        else if(a1==0 && b1==0 && c1==0) ans=-1;
        else if(a2==0 && b2==0 && c2==0) ans=-1;
        else {
            long long z=a1*b2-b1*a2;
            if(z==0){
                long long x=c1*b2-b1*c2;
                long long y=a1*c2-c1*a2;
                ans=(x==0 && y==0 ? -1 : 0);
            } else ans=1;
        }
    }
    cout<<ans;
}
