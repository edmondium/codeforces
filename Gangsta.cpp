#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        string s;
        cin >> n >> s;

        // 1) total length-sum = n(n+1)(n+2)/6
        ll total_len = (ll)n * (n + 1) * (n + 2) / 6;

        // 2) build prefix-diff A[0..n]
        vector<ll> A(n+1);
        A[0] = 0;
        for(int i = 0; i < n; i++){
            A[i+1] = A[i] + (s[i]=='1' ? +1 : -1);
        }

        // 3) sort into B, compute sum |differences|
        sort(A.begin(), A.end());
        ll m = n + 1;           // size of A
        ll sum_diff = 0;
        for(ll k = 0; k < m; k++){
            // each A[k] contributes A[k] * (#times it's the bigger minus #times it's the smaller)
            // = A[k] * (k - (m-1-k)) = A[k] * (2k - (m-1))
            sum_diff += A[k] * (2*k - (m-1));
        }

        // final answer
        // (total_len + sum_diff) is always even, divide by 2
        ll ans = (total_len + sum_diff) / 2;
        cout << ans << "\n";
    }

    return 0;
}
