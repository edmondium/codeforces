#include <iostream>
#include <vector>
#include <limits>
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
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
 
        // if all entries are the same, nothing needs to be done
        bool allSame = true;
        for (int i = 1; i < n; i++){
            if(a[i] != a[0]){
                allSame = false;
                break;
            }
        }
        if(allSame){
            cout << 0 << "\n";
            continue;
        }
 
        // We “simulate” a propagation strategy.
        // The idea: for any contiguous block in the original array where the value is v,
        // one valid strategy is:
        //    - use one operation to make indices 1..(L-1) equal to v (cost = (L-1)*v)
        //    - use one operation to make indices (R+1)..n equal to v (cost = (n-R)*v)
        // Total cost candidate = ((L-1) + (n-R)) * v.
        //
        // Over all maximal contiguous segments (blocks) in the array we take the minimum candidate.
        // (The reason this works is that if you plan operations “from the ends inward” then you may update
        // a whole block at once; no sequence can beat that cost.)
 
        long long ans = numeric_limits<long long>::max();
        // process the array to find contiguous blocks (each block is [L,R] where all a[i]==v)
        for (int i = 0; i < n; ){
            int v = a[i];
            int L = i + 1; // converting to 1-indexed; L = start index of current block
            int R = L;
            while(i < n && a[i] == v){
                i++;
                R++;
            }
            // [L, R-1] is a contiguous block with value v.
            int blockL = L, blockR = R - 1;
            long long costCandidate = (long long)((blockL - 1) + (n - blockR)) * v;
            ans = min(ans, costCandidate);
        }
 
        cout << ans << "\n";
    }
    return 0;
}
