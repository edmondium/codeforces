#include<bits/stdc++.h>
using namespace std;
void testCase() {
    string s;
    int n;
    cin >> n;
    cin >> s;
    s="0"+s;
    int ans = 0, cur = s[0];
    for (int i = 1; i <= n; i++) {
        int dig = s[i];
        if (cur != dig) 
           ans++;
        cur = dig;
    }
   if(ans>=3)
     cout<< ans-2 + n<< endl;
   else if(ans==2)
     cout<< ans-1 + n<< endl;
   else 
     cout<<ans+n<< endl;
}
int main(){
    int t;
    cin>>t;
    while(t--)
        testCase();
    return 0;
}