#include <iostream>
#include <string>
#include <array>
using namespace std;

// Function to check if the remaining positions (from pos to 9)
// can be filled with the remaining frequency counts stored in f.
// For each threshold r = 0,...,9, we need to ensure that the number
// of available digits with value >= r is at least the number of positions
// among [pos, 9] whose requirement (which is 10 - (j+1)) is >= r.
// A quick derivation shows that the number of positions needing a digit >= r is:
//   max(0, 10 - r - pos)
bool feasible(int pos, const array<int,10>& f) {
    for (int r = 0; r < 10; r++) {
        int needed = 10 - r - pos;
        if (needed < 0) needed = 0;
        int available = 0;
        for (int d = r; d < 10; d++) {
            available += f[d];
        }
        if (available < needed)
            return false;
    }
    return true;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        // Count frequencies of the 10 digits
        array<int,10> freq = {0,0,0,0,0,0,0,0,0,0};
        for (char c : s)
            freq[c - '0']++;
 
        // We build the answer one digit at a time.
        // Note: at position pos (0-indexed) the minimum allowed digit is:
        //       required = 10 - (pos+1)
        string ans(10, ' ');
        for (int pos = 0; pos < 10; pos++){
            int req = 10 - (pos + 1);
            // Try digits d starting from req up to 9
            for (int d = req; d < 10; d++){
                if(freq[d] > 0){
                    freq[d]--; // choose this digit tentatively
                    // Check if with this choice we can fill positions pos+1 ... 9.
                    if(feasible(pos + 1, freq)){
                        ans[pos] = char('0' + d);
                        break;
                    }
                    // Otherwise restore and try a larger candidate.
                    freq[d]++;
                }
            }
        }
 
        cout << ans << "\n";
    }
    return 0;
}
