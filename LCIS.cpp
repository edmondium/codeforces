#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Solves the Longest Common Increasing Subsequence (LCIS) problem.
 */
void solve() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int m;
    std::cin >> m;
    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    // dp[j] = length of LCIS using a prefix of a and b[0...j], ending in b[j].
    std::vector<int> dp(m, 0);
    // parent[j] = index in b of the predecessor for the LCIS ending at b[j].
    std::vector<int> parent(m, -1);

    // Iterate through each element of the first sequence 'a'
    for (int i = 0; i < n; ++i) {
        int current_length = 0;
        int last_idx = -1;

        // Iterate through each element of the second sequence 'b'
        for (int j = 0; j < m; ++j) {
            // Case 1: a[i] == b[j]. We can potentially form a new LCIS.
            // Its length would be 1 + the longest LCIS ending in a value smaller than a[i].
            if (a[i] == b[j]) {
                if (current_length + 1 > dp[j]) {
                    dp[j] = current_length + 1;
                    parent[j] = last_idx;
                }
            }
            
            // Case 2: a[i] > b[j]. b[j] is a candidate for being a predecessor.
            // We find the longest LCIS so far that ends in a value smaller than a[i].
            if (a[i] > b[j]) {
                if (dp[j] > current_length) {
                    current_length = dp[j];
                    last_idx = j;
                }
            }
        }
    }

    // Find the length and the ending index of the overall LCIS
    int max_len = 0;
    int end_idx = -1;
    for (int j = 0; j < m; ++j) {
        if (dp[j] > max_len) {
            max_len = dp[j];
            end_idx = j;
        }
    }

    // Output the length
    std::cout << max_len << std::endl;

    // Reconstruct and print the LCIS path by backtracking
    if (max_len > 0) {
        std::vector<int> result;
        int current_idx = end_idx;
        while (current_idx != -1) {
            result.push_back(b[current_idx]);
            current_idx = parent[current_idx];
        }
        std::reverse(result.begin(), result.end());

        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }
}

int main() {
    solve();
    return 0;
}