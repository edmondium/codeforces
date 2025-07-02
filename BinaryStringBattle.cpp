#include <iostream>
#include <string>
#include <vector>
#include <numeric>

// Function to solve a single test case
void solve() {
    int n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;

    // 1. Count the initial number of '1's in the string.
    int ones_count = 0;
    for (char c : s) {
        if (c == '1') {
            ones_count++;
        }
    }

    // 2. Alice wins if she can clear all '1's in her first move.
    if (ones_count <= k) {
        std::cout << "Alice" << std::endl;
        return;
    }

    // 3. Analyze the board size relative to the move size 'k'.
    if (2 * k > n) {
        // If the board is "small", any two k-substrings overlap.
        // Bob cannot create an independent stronghold. Alice wins.
        std::cout << "Alice" << std::endl;
    } else {
        // If the board is "large" enough for two disjoint k-substrings,
        // Bob can create a stronghold and perpetually prevent Alice from winning.
        std::cout << "Bob" << std::endl;
    }
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Read the number of test cases
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}