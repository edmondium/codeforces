#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        // Print k ones, then n-k zeros
        cout << string(k, '1') << string(n - k, '0') << "\n";
    }
    return 0;
}
