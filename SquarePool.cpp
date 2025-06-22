#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n;
        ll s;
        cin >> n >> s;
        ll cnt = 0;
        for(int i = 0; i < n; i++){
            int dx, dy;
            ll x, y;
            cin >> dx >> dy >> x >> y;
            // Riding ↘ or ↖ diagonal: need x == y
            if(dx == dy){
                if(x == y) 
                    cnt++;
            }
            // Riding ↗ or ↙ diagonal: need x + y == s
            else { // dx == -dy
                if(x + y == s) 
                    cnt++;
            }
        }
        cout << cnt << "\n";
    }
    return 0;
}
