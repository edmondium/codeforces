#include <iostream>
#include <cmath>
#include <algorithm>

// Function to solve a single test case
void solve() {
    int a, x, y;
    std::cin >> a >> x >> y;

    // Calculate Alice's distance to each potential prize location. 
    int dist_ax = std::abs(a - x);
    int dist_ay = std::abs(a - y);

    // For Bob to win, his distance must be strictly less than Alice's. 
    // This defines a range of possible integer starting points 'b' for each prize location.
    // For prize at x: |b - x| < dist_ax  =>  b is in the integer range [x - dist_ax + 1, x + dist_ax - 1]
    // For prize at y: |b - y| < dist_ay  =>  b is in the integer range [y - dist_ay + 1, y + dist_ay - 1]

    int lower_bound_x = x - dist_ax + 1;
    int upper_bound_x = x + dist_ax - 1;

    int lower_bound_y = y - dist_ay + 1;
    int upper_bound_y = y + dist_ay - 1;

    // Bob needs a point 'b' that is in the intersection of both ranges.
    int final_lower_bound = std::max(lower_bound_x, lower_bound_y);
    int final_upper_bound = std::min(upper_bound_x, upper_bound_y);

    // Check if a valid integer point exists in the final range [final_lower_bound, final_upper_bound].
    // A point is valid if it exists and is not equal to Alice's starting point 'a'. 

    // Condition for NO:
    // 1. The intersection range is empty.
    // 2. The intersection range contains only one point, and that point is 'a'.
    if (final_lower_bound > final_upper_bound || (final_lower_bound == final_upper_bound && final_lower_bound == a)) {
        std::cout << "NO\n";
    } else {
        // Otherwise, a valid point for Bob is guaranteed to exist.
        std::cout << "YES\n";
    }
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Read the number of test cases. 
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}