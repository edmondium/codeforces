#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool check(long long ans, int n, const vector<long long>& a) {
    // Create a difference array to simulate the cascading increments.
    vector<long long> d(n, 0LL);
    long long acc = 0;
    
    for (int i = 0; i < n; i++) {
        // Subtract pending increments scheduled to stop at i.
        acc -= d[i];

        // Calculate how many extra increments are needed for the simulation
        long long need = max(0LL, static_cast<long long>(i) - (n - ans));
        if (acc < need)
            return false;
        
        // Capture the current acc value before post-increment:
        long long oldAcc = acc;
        acc++;  // simulate the post-increment as used in the original formula
        
        // Determine the last index (one past the end of the increment interval) affected.
        long long end = i + a[i] + oldAcc - need + 1;
        if (end < n) {
            d[end]++;
        }
    }
    
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // We binary search for the maximum MEX.
        // The lower bound starts at 1 and upper bound is n+1,
        // as with n towers the best achievable MEX is at most n.
        long long le = 1, ri = n + 1, mid;
        while (ri - le > 1) {
            mid = (le + ri) / 2;
            if (check(mid, n, a)) {
                le = mid;
            } else {
                ri = mid;
            }
        }
        
        cout << le << "\n";
    }
    
    return 0;
}
