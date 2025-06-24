#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Function to solve a single test case
void solve() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    long long win_count = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // We have chosen a[i] and a[j]. We need to find the number of valid k > j.
            
            // Condition 1: a[i] + a[j] > a[k]
            // This means a[k] must be less than a[i] + a[j].
            long long upper_bound_val = a[i] + a[j];
            
            // Find the range of possible k's that satisfy a[k] < upper_bound_val.
            // These are indices from j+1 up to the element just before the lower_bound of upper_bound_val.
            auto k_candidate_start_it = a.begin() + j + 1;
            auto k_candidate_end_it = std::lower_bound(k_candidate_start_it, a.end(), upper_bound_val);

            if (k_candidate_start_it >= k_candidate_end_it) {
                continue; // No k > j satisfies the first condition.
            }

            // Now, among these candidates, check the second condition:
            // a[i] + a[j] + a[k] > max_other
            
            // Case A: k < n-1. max_other is a[n-1].
            // We need a[k] > a[n-1] - a[i] - a[j].
            long long lower_bound_val_A = a[n-1] - a[i] - a[j];
            
            auto case_A_end_it = std::min(k_candidate_end_it, a.begin() + n - 1);
            auto valid_k_start_it = std::upper_bound(k_candidate_start_it, case_A_end_it, lower_bound_val_A);
            
            win_count += std::distance(valid_k_start_it, case_A_end_it);

            // Case B: k = n-1.
            // This k is a candidate if it satisfied the first condition: a[n-1] < a[i] + a[j].
            // This is true if k_candidate_end_it includes or is past the last element.
            if (k_candidate_end_it == a.end()) {
                // Check the second condition for k = n-1. max_other is a[n-2].
                // Note: n>=3 is a constraint, so n-2 is a valid index.
                if (a[i] + a[j] + a[n-1] > a[n-2]) {
                    win_count++;
                }
            }
        }
    }

    std::cout << win_count << std::endl;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}