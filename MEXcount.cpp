#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int> cnt(n+1,0), a(n);
        for(int &x : a){
            cin >> x;
            if(x <= n) 
                cnt[x]++;
        }

        // Prepare difference array
        vector<int> diff(n+2, 0);

        // Track if any i<m is missing
        bool feasible = true;
        for(int m = 0; m <= n && feasible; m++){
            // Check that all 0..m-1 exist
            if(m > 0 && cnt[m-1] == 0){
                feasible = false;
                break;
            }
            // Determine low & high bounds
            int low  = (cnt[m] > 0 ? cnt[m] : 0);
            int high = n - m;
            if(low <= high){
                diff[low]  += 1;
                diff[high+1] -= 1;
            }
        }

        // Build answers via prefix sum of diff
        vector<int> ans(n+1);
        ans[0] = diff[0];
        for(int k = 1; k <= n; k++){
            ans[k] = ans[k-1] + diff[k];
        }

        // Print
        for(int k = 0; k <= n; k++){
            cout << ans[k] << (k < n ? ' ' : '\n');
        }
    }
    return 0;
}
