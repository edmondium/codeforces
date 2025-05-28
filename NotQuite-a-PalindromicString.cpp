#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        
        // Count the number of zeros in the string.
        int count0 = 0;
        for (char ch : s) {
            if (ch == '0') {
                count0++;
            }
        }
        
        // Total number of pairs from positions (i, n-i+1).
        int m = n / 2;
        
        // We can rearrange the string into m pairs.
        // For exactly k good pairs:
        //   Let 'a' = number of good pairs that are "00"; then the rest k - a are "11".
        //   Each "00" pair uses two zeros, and each "not-good" pair uses one zero.
        //   Total zeros used = 2*a + (m - k).
        //
        // Solving for a:
        //   2*a = count0 - (m - k)  -->  a = (count0 - (m - k)) / 2.
        //
        // For a valid rearrangement we need:
        //   (1) count0 must lie between m - k and m + k.
        //   (2) (count0 - (m - k)) must be even (making a an integer).
        //   (3) a must be between 0 and k (due to assignment into "00" pairs).
        //
        // Note that if (1) and (2) hold then automatically a is in [0, k].
        if (count0 < m - k || count0 > m + k || ((count0 - (m - k)) % 2 != 0)) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    
    return 0;
}
