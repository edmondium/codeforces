#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Checks if two value ranges are "close" enough to satisfy the beautiful condition.
// A range [min1, max1] is close to [min2, max2] if there exist x in the first
// and y in the second such that |x - y| <= 1.
bool are_ranges_close(long long min1, long long max1, long long min2, long long max2) {
    return max(min1, min2) <= min(max1, max2) + 1;
}

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (n < 2) {
        cout << -1 << endl;
        return;
    }

    // Case 0: Check if the array is already beautiful.
    for (int i = 0; i < n - 1; ++i) {
        if (abs(a[i] - a[i + 1]) <= 1) {
            cout << 0 << endl;
            return;
        }
    }
    
    if (n == 2) {
        cout << -1 << endl;
        return;
    }

    long long min_ops = -1;

    // Precompute ranges for all subarrays O(n^2)
    vector<vector<pair<long long, long long>>> ranges(n, vector<pair<long long, long long>>(n));
    for (int i = 0; i < n; ++i) {
        ranges[i][i] = {a[i], a[i]};
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            ranges[i][j] = {min(ranges[i][j - 1].first, a[j]), max(ranges[i][j - 1].second, a[j])};
        }
    }

    // Case A: A single merged block becomes beautiful with an adjacent original element. (O(n^2))
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            long long current_ops = j - i;
            long long min_val = ranges[i][j].first;
            long long max_val = ranges[i][j].second;

            if (i > 0) {
                if (are_ranges_close(min_val, max_val, a[i - 1], a[i - 1])) {
                    if (min_ops == -1 || current_ops < min_ops) {
                        min_ops = current_ops;
                    }
                }
            }
            if (j < n - 1) {
                if (are_ranges_close(min_val, max_val, a[j + 1], a[j + 1])) {
                    if (min_ops == -1 || current_ops < min_ops) {
                        min_ops = current_ops;
                    }
                }
            }
        }
    }

    // REVISED and FIXED Case B: Two adjacent merged blocks (O(n^2) with two pointers)
    for (int j = 0; j < n - 1; ++j) { // j is the split point
        int i_ptr = 0; // The second pointer, for the start of the left block
        for (int k = j + 1; k < n; ++k) { // Iterate through all possible right blocks
            
            // Unpack the right block's range
            long long min2 = ranges[j + 1][k].first;
            long long max2 = ranges[j + 1][k].second;

            // Advance the i_ptr
            while (i_ptr < j && are_ranges_close(ranges[i_ptr + 1][j].first, ranges[i_ptr + 1][j].second, min2, max2)) {
                i_ptr++;
            }

            // Check if the current best pair (i_ptr, k) works and update the minimum operations.
            if (are_ranges_close(ranges[i_ptr][j].first, ranges[i_ptr][j].second, min2, max2)) {
                long long current_ops = (long long)(j - i_ptr) + (k - (j + 1));
                if (min_ops == -1 || current_ops < min_ops) {
                    min_ops = current_ops;
                }
            }
        }
    }
    
    cout << min_ops << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}