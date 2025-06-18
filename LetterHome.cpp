// C++23
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T; 
    cin >> T;
    while(T--){
        int n, s;
        cin >> n >> s;
        vector<int> x(n);
        for(int &xi : x) cin >> xi;
        // x is guaranteed strictly increasing
        int lo = x.front();
        int hi = x.back();
        int span = hi - lo;
        int to_end = min(abs(s - lo), abs(s - hi));
        cout << span + to_end << "\n";
    }
    return 0;
}
