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
        long long k;
        cin >> n >> k;
        vector<long long> a(n), b(n);
        
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < n; i++){
            cin >> b[i];
        }
 
        bool valid = true;
        bool candidateSet = false;
        long long candidate = 0;
        
        // Determine candidate x from any non-missing b[i]
        for (int i = 0; i < n; i++){
            if(b[i] != -1){
                long long sum = a[i] + b[i];
                if(!candidateSet){
                    candidateSet = true;
                    candidate = sum;
                } else if(sum != candidate){
                    valid = false;
                    break;
                }
            }
        }
 
        if(!valid){
            cout << 0 << "\n";
            continue;
        }
 
        if(candidateSet){
            // With candidate determined, verify missing entries can be filled.
            for (int i = 0; i < n; i++){
                long long expected = candidate - a[i];
                if(expected < 0 || expected > k){
                    valid = false;
                    break;
                }
            }
            cout << (valid ? 1 : 0) << "\n";
        } 
        else {
            // All entries are missing.
            // For each index i, if we set b[i] = x - a[i] then we need:
            //    0 <= x - a[i] <= k  ==>  a[i] <= x <= k + a[i]
            // So x must lie in the intersection of [a[i], a[i]+k] for all i.
            // That is: x ∈ [ L, R ] where L = max{ a[i] } and R = min{ a[i] + k }.
            long long L = *max_element(a.begin(), a.end());
            long long R = *min_element(a.begin(), a.end()) + k;
            if(L > R) cout << 0 << "\n";
            else cout << (R - L + 1) << "\n";
        }
    }
    return 0;
}
