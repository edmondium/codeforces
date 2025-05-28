#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        // Use 1-indexing for d to make the correspondence to obstacles natural.
        vector<int> d(n+1, 0);
        for (int i = 1; i <= n; i++){
            cin >> d[i];
        }
        vector<int> li(n+1, 0), ri(n+1, 0);
        for (int i = 1; i <= n; i++){
            cin >> li[i] >> ri[i];
        }
 
        // Forward DP: L[i], R[i] = reachable interval of h[i] after i steps.
        // h[0] = 0.
        vector<int> L(n+1, 0), R(n+1, 0);
        L[0] = 0; 
        R[0] = 0;
        bool possible = true;
        for (int i = 1; i <= n; i++){
            int low, high;
            if(d[i] != -1){
                // Fixed step: add d[i] (either 0 or 1)
                int inc = d[i];
                low = L[i-1] + inc;
                high = R[i-1] + inc;
            } else {
                // Unknown: we can choose 0 or 1.
                low = L[i-1] + 0;
                high = R[i-1] + 1;
            }
            // Intersect possible heights with the obstacle’s constraint.
            low  = max(low, li[i]);
            high = min(high, ri[i]);
 
            if (low > high){
                possible = false;
                break;
            }
            L[i] = low;
            R[i] = high;
        }
 
        if(!possible){
            cout << -1 << "\n";
            continue;
        }
        
        // Backward reconstruction:
        // Choose a final height h[n] from the interval [L[n], R[n]]. We choose h[n] = L[n].
        vector<int> h(n+1, 0);
        h[n] = L[n];
        // 'ans' will store our decisions for d[1...n]
        vector<int> ans(n+1, 0);
 
        for (int i = n; i >= 1; i--){
            if(d[i] != -1){
                // With fixed d[i], we have h[i] = h[i-1] + d[i]
                int prev = h[i] - d[i];
                if (prev < L[i-1] || prev > R[i-1]){
                    possible = false;
                    break;
                }
                h[i-1] = prev;
                ans[i] = d[i];
            } else {
                // d[i] is unknown. Try to choose 0 if possible.
                if (h[i] >= L[i-1] && h[i] <= R[i-1]){
                    ans[i] = 0;
                    h[i-1] = h[i];
                } else {
                    // Otherwise the only possibility is to use 1.
                    if (h[i] - 1 >= L[i-1] && h[i]-1 <= R[i-1]){
                        ans[i] = 1;
                        h[i-1] = h[i] - 1;
                    } else {
                        possible = false;
                        break;
                    }
                }
            }
        }
 
        if(!possible){
            cout << -1 << "\n";
            continue;
        }
 
        // Output the flight program decision for positions 1..n.
        for (int i = 1; i <= n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
