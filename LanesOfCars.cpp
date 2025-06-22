#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Use 128-bit integer for sums to avoid overflow, as S*S can be large.
using int128 = __int128_t;

// Helper function to calculate the number of cars a single lane `i`
// would take if the marginal cost threshold is C.
long long count_cars_for_lane(long long C, long long a_i, long long k) {
    long long count = 0;
    // Case 1: Cars up to the original count a_i
    // Marginal cost is x+1-k. We need x+1-k <= C  => x <= C+k-1
    if (C + k - 1 >= 0) {
        count += std::min((long long)a_i, C + k);
    }
    // Case 2: Cars beyond the original count a_i
    // Marginal cost is x+1. We need x+1 <= C => x <= C-1
    if (C - 1 >= a_i) {
        count += (C - 1) - a_i + 1;
    }
    return count;
}


void solve() {
    int n;
    long long k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    long long total_cars = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        total_cars += a[i];
    }

    if (total_cars == 0) {
        std::cout << 0 << "\n";
        return;
    }

    // Binary search for the marginal cost of the last car.
    long long low = -k - 1e7, high = 2e11 + k, ans_C = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long current_cars = 0;
        for (int i = 0; i < n; ++i) {
            current_cars += count_cars_for_lane(mid, a[i], k);
            if (current_cars > total_cars) break; // Optimization to prevent overflow
        }

        if (current_cars >= total_cars) {
            ans_C = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    // Now we have the threshold cost `ans_C`.
    // We calculate the final number of cars in each lane.
    std::vector<long long> final_counts(n);
    long long cars_less_than_ans_C = 0;
    for (int i = 0; i < n; ++i) {
        final_counts[i] = count_cars_for_lane(ans_C - 1, a[i], k);
        cars_less_than_ans_C += final_counts[i];
    }

    long long remaining_cars = total_cars - cars_less_than_ans_C;

    // Distribute the remaining cars to lanes where the marginal cost is exactly ans_C.
    for (int i = 0; i < n; ++i) {
        if (remaining_cars == 0) break;
        long long current_lane_cars = final_counts[i];
        long long next_marginal_cost;
        if (current_lane_cars < a[i]) {
            next_marginal_cost = current_lane_cars + 1 - k;
        } else {
            next_marginal_cost = current_lane_cars + 1;
        }
        if (next_marginal_cost == ans_C) {
            final_counts[i]++;
            remaining_cars--;
        }
    }
    
    // Calculate the final total angriness using the determined lane counts.
    int128 total_angriness = 0;
    for (int i = 0; i < n; ++i) {
        int128 c = final_counts[i];
        total_angriness += c * (c + 1) / 2;
        if (a[i] > c) {
            total_angriness += (int128)k * (a[i] - c);
        }
    }

    std::cout << (long long)total_angriness << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
