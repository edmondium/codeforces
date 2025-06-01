#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        
        // Step 1. Compute the overall gcd (g) of the array.
        int g = 0;
        for (int x : a) {
            g = std::gcd(g, x);
        }
        
        // Count how many numbers already equal g.
        int countGood = 0;
        for (int x : a) {
            if(x == g)
                countGood++;
        }
        
        // If there is at least one "good" element, no extra move is needed
        // to “create” a g; we only need to propagate it.
        if(countGood > 0){
            cout << (n - countGood) << "\n";
            continue;
        }
        
        // Otherwise, we must “manufacture” a g by combining some subsequence.
        // Let dp[x] be the minimum number of elements (in a subsequence) whose gcd is x.
        // Since all a[i] are <= 5000, we set our dp array size accordingly.
        const int MAX = 5000;
        const int INF = 1e9;
        vector<int> dp(MAX + 1, INF);
        
        // Process the array elements one by one.
        // The order is irrelevant since gcd is commutative.
        for (int x : a) {
            // We'll update dp in a temporary copy so that the current element 
            // isn’t reused twice in this iteration.
            vector<int> new_dp = dp;
            new_dp[x] = 1; // using the single element x gives gcd = x.
            for (int d = 1; d <= MAX; d++) {
                if(dp[d] != INF){
                    int new_g = std::gcd(d, x);
                    new_dp[new_g] = min(new_dp[new_g], dp[d] + 1);
                }
            }
            dp = new_dp;
        }
        
        // Let m = dp[g] be the minimum number of elements needed to get gcd equal to g.
        int m = dp[g];
        // Then the minimum operations required is:
        //   (n - 1) [to propagate a "g"] + (m - 1) [to create one "g"]
        int ans = (n - 1) + (m - 1);
        cout << ans << "\n";
    }
    return 0;
}
