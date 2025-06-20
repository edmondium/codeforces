#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

/**
 * Solves the Cinema Cashier problem by simulating the seat selection process.
 */
void solve() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k;

    // Hall state: true if occupied, false if free. Using 1-based indexing.
    std::vector<std::vector<bool>> is_occupied(k + 1, std::vector<bool>(k + 1, false));

    // Calculate center coordinates
    int x_c = (k + 1) / 2;
    int y_c = (k + 1) / 2;

    // Precompute prefix sums for the y-component of the remoteness function
    std::vector<long long> y_prefix_remoteness(k + 1, 0);
    for (int y = 1; y <= k; ++y) {
        y_prefix_remoteness[y] = y_prefix_remoteness[y - 1] + std::abs(y - y_c);
    }

    // Process each of the N requests
    for (int i = 0; i < n; ++i) {
        int m; // Number of seats for the current request
        std::cin >> m;

        long long min_remoteness = -1;
        int best_x = -1, best_y_l = -1;

        // Iterate through all rows to find the best placement
        for (int x = 1; x <= k; ++x) {
            // Find all available blocks of size m in the current row
            int consecutive_free = 0;
            for (int y = 1; y <= k; ++y) {
                if (!is_occupied[x][y]) {
                    consecutive_free++;
                } else {
                    consecutive_free = 0;
                }

                // If a valid block is found (ending at seat y)
                if (consecutive_free >= m) {
                    int y_l = y - m + 1;
                    int y_r = y;

                    // Calculate remoteness for this block using the precomputed prefix sums
                    long long y_remoteness = y_prefix_remoteness[y_r] - y_prefix_remoteness[y_l - 1];
                    long long total_remoteness = (long long)m * std::abs(x - x_c) + y_remoteness;

                    // If this block is better than the best one found so far, update.
                    // The loop order (increasing x, then increasing y_l) naturally handles tie-breakers.
                    if (min_remoteness == -1 || total_remoteness < min_remoteness) {
                        min_remoteness = total_remoteness;
                        best_x = x;
                        best_y_l = y_l;
                    }
                }
            }
        }

        // Output the result for the current request
        if (best_x == -1) {
            std::cout << -1 << "\n";
        } else {
            int best_y_r = best_y_l + m - 1;
            std::cout << best_x << " " << best_y_l << " " << best_y_r << "\n";
            // Mark the chosen seats as occupied for subsequent requests
            for (int y = best_y_l; y <= best_y_r; ++y) {
                is_occupied[best_x][y] = true;
            }
        }
    }
}

int main() {
    solve();
    return 0;
}