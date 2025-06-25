#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<int>a(n);
    for(int &x:a) cin >> x;

    // 0 operations if already beautiful
    for(int i=1;i<n;i++){
        if(abs(a[i-1]-a[i])<=1){
            cout<<"0\n";
            return;
        }
    }

    // 1 operation if there's any peak or valley
    for(int i=1;i+1<n;i++){
        if( (a[i-1]<a[i] && a[i]>a[i+1])
         || (a[i-1]>a[i] && a[i]<a[i+1]) ){
            cout<<"1\n";
            return;
        }
    }

    // otherwise impossible
    cout<<"-1\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
