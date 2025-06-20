#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

/**
 * Solves the Power Consumption Calculation problem.
 * This function reads the input values, calculates the total power consumption
 * based on the logic of work periods and idle periods, and prints the result.
 */
void solve() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    long long p1, p2, p3, t1, t2;

    // Read problem parameters 
    std::cin >> n >> p1 >> p2 >> p3 >> t1 >> t2;

    std::vector<int> l(n), r(n);
    // Read n work periods 
    for (int i = 0; i < n; ++i) {
        std::cin >> l[i] >> r[i];
    }

    long long total_power = 0;

    // Calculate power for the first work period and subsequent idle/work periods
    for (int i = 0; i < n; ++i) {
        // Add power consumed during the current active work period
        total_power += (long long)(r[i] - l[i]) * p1;

        // If this is not the last period, calculate power for the idle time that follows
        if (i < n - 1) {
            int idle_duration = l[i + 1] - r[i];

            // Power during the normal mode phase of the idle time
            long long time_in_normal_idle = std::min((long long)idle_duration, t1);
            total_power += time_in_normal_idle * p1;

            // Power during the screensaver phase of the idle time
            long long time_in_screensaver = std::min((long long)std::max(0, idle_duration - (int)t1), t2);
            total_power += time_in_screensaver * p2;

            // Power during the sleep mode phase of the idle time
            long long time_in_sleep = std::max(0, idle_duration - (int)t1 - (int)t2);
            total_power += time_in_sleep * p3;
        }
    }

    // Output the final calculated power 
    std::cout << total_power << std::endl;
}

int main() {
    solve();
    return 0;
}