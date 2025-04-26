#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; 
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<long long> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        
        // We are allowed to remove at most k bars.
        // Hence, the number of open bars m is at least n - k.
        // In an optimal (contiguous) configuration, the minimizer set is
        // either a single number (if m is odd) or, if m is even,
        // the entire interval [B[p-1], B[n-p]], where:
        //   p = (n - k)/2  if (n-k) is even,
        //   p = (n - k + 1)/2  if (n-k) is odd.
        int totalOpen = n - k; // minimum open bars we must keep
        int p;
        if(totalOpen % 2 == 0)
            p = totalOpen / 2;
        else
            p = (totalOpen + 1) / 2;
 
        // In our 0-indexed sorted array:
        // The candidate interval is from a[p-1] to a[n-p]
        long long Lb = a[p - 1];       
        long long Rb = a[n - p];
        long long ans = max(0LL, Rb - Lb + 1);
        cout << ans << "\n";
    }
    return 0;
}
