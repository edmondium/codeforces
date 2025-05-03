#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    
    // We'll use INF = n (since valid indices are 0..n-1, n means "not found")
    const int INF = n;
    
    // Precompute nxt array using a 1D vector that represents a (n+1) x k matrix.
    // nxt[i][c] is stored at nxt[i*k + c].
    // For i == n (i.e. past the end of s) every letter is not found.
    vector<int> nxt((n + 1) * k, INF);
    for (int c = 0; c < k; c++) {
        nxt[n * k + c] = INF;
    }
    
    // Build nxt from the back: for i from n-1 down to 0, copy the next row and override for the letter at s[i].
    for (int i = n - 1; i >= 0; i--) {
        for (int c = 0; c < k; c++) {
            nxt[i * k + c] = nxt[(i + 1) * k + c];
        }
        int letter = s[i] - 'a';
        nxt[i * k + letter] = i;
    }
    
    // Precompute dp: dp[i] = minimal appended letters needed when starting from position i in s.
    // Base case: from position n (past the end), any letter will fail since there are no remaining characters.
    vector<int> dp(n + 1, 0);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        int best = INT_MAX;
        for (int c = 0; c < k; c++) {
            int nextIndex = nxt[i * k + c];
            // If letter c does not appear starting from i, one letter is enough.
            if (nextIndex == INF) {
                best = 1;
                break;
            } else {
                best = min(best, 1 + dp[nextIndex + 1]);
            }
        }
        dp[i] = best;
    }
    
    // Process the queries.
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        int pos = 0;
        bool alreadyUnpleasant = false;
        // Simulate subsequence matching for query t in s.
        for (char ch : t) {
            int letter = ch - 'a';  // letter index in 0...k-1
            if (pos > n) break;     // sanity check (pos will always be <= n when matching properly)
            int posFound = nxt[pos * k + letter];
            if (posFound == INF) {
                alreadyUnpleasant = true;
                break;
            }
            pos = posFound + 1;
        }
        // If the query string isn't a subsequence, no need to append any letters.
        if (alreadyUnpleasant) {
            cout << 0 << "\n";
        } else {
            // Otherwise, the answer is the minimum appended letters needed from the current state.
            cout << dp[pos] << "\n";
        }
    }
    
    return 0;
}
