#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;

        // Count all letters
        array<int,26> freq{};
        for (char c : s) 
            ++freq[c - 'a'];

        bool ok = false;
        // Try b = s[i] for each interior i
        for (int i = 1; i <= n - 2; i++) {
            int idx = s[i] - 'a';
            --freq[idx];              // remove this occurrence
            if (freq[idx] > 0) {      // found another copy elsewhere
                ok = true;
                break;
            }
            // if not used, we'll never need this s[i] again
        }

        cout << (ok ? "Yes\n" : "No\n");
    }
    return 0;
}
