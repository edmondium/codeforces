#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        int64 k;
        cin >> n >> k;
        vector<int64> a(n);
        for(int i = 0; i < n; i++) 
            cin >> a[i];

        int64 mn = LLONG_MAX, mx = LLONG_MIN;
        int64 S = 0;
        for(auto x : a){
            S += x;
            mn = min(mn, x);
            mx = max(mx, x);
        }
        int64 delta = mx - mn;

        // Count how many boxes currently have the maximum
        int cnt_mx = 0;
        for(auto x : a) if(x == mx) cnt_mx++;

        bool tom_wins;
        if(delta > k + 1) {
            // No safe first move → Tom loses
            tom_wins = false;
        }
        else if(delta == k + 1) {
            // Only if the maximum is unique can Tom make that one safe move
            if(cnt_mx == 1) {
                // After that forced move, the game becomes “delta ≤ k” on S-1 apples,
                // and one can show overall the parity of S still decides.
                tom_wins = (S % 2 == 1);
            } else {
                // Multiple maxima → removing from one leaves another, so delta remains k+1>k → illegal
                tom_wins = false;
            }
        }
        else {
            // delta ≤ k: no gap-constraint ever forbids a move, so it's just “take 1 apple per turn”
            tom_wins = (S % 2 == 1);
        }

        cout << (tom_wins ? "Tom\n" : "Jerry\n");
    }
    return 0;
}
