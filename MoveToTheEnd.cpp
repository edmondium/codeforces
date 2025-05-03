#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // Compute suffix sums:
        // suffix[i] = sum of elements from a[i] to a[n-1]
        vector<ll> suffix(n + 1, 0);
        suffix[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + a[i];
        }
        
        // Compute prefix maximums:
        // prefix_max[i] = max(a[0], a[1], ..., a[i])
        vector<ll> prefix_max(n, 0);
        prefix_max[0] = a[0];
        for (int i = 1; i < n; i++) {
            prefix_max[i] = max(prefix_max[i - 1], a[i]);
        }
        
        // For each k from 1 to n:
        // Possibility 1 (choose an element already in the tail):
        //    ans1 = sum of last k elements = suffix[n - k]
        // Possibility 2 (choose an element from the head):
        //    ans2 = [max among the first (n-k) elements] + sum of last (k-1) elements = prefix_max[n - k - 1] + suffix[n - k + 1]
        // (Note: if n - k == 0 then possibility 2 cannot be used.)
        for (int k = 1; k <= n; k++) {
            ll ans = suffix[n - k];  // Possibility 1.
            if (n - k > 0) {
                ll candidate = prefix_max[n - k - 1] + suffix[n - k + 1];
                ans = max(ans, candidate);
            }
            cout << ans << " ";
        }
        cout << "\n";
    }

    return 0;
}
