#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>

void solve() {
    int n;
    long long m;
    int q;
    std::cin >> n >> m >> q;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Find all divisors of m
    std::vector<long long> divisors;
    for (long long i = 1; i * i <= m; ++i) {
        if (m % i == 0) {
            divisors.push_back(i);
            if (i * i != m) {
                divisors.push_back(m / i);
            }
        }
    }
    std::sort(divisors.begin(), divisors.end());

    std::map<long long, int> div_to_idx;
    for (int i = 0; i < divisors.size(); ++i) {
        div_to_idx[divisors[i]] = i;
    }
    
    int num_divisors = divisors.size();
    std::vector<long long> counts(num_divisors, 0);

    // Initial calculation of counts
    for (int j = 0; j < num_divisors; ++j) {
        long long g = divisors[j];
        for (int i = 0; i < n - 1; ++i) {
            if ((a[i] % g) > (a[i + 1] % g)) {
                counts[j]++;
            }
        }
    }

    for (int k_query = 0; k_query < q; ++k_query) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int i;
            long long x;
            std::cin >> i >> x;
            --i; // 0-indexed

            long long old_val = a[i];
            if (old_val == x) {
                continue;
            }

            for (int j = 0; j < num_divisors; ++j) {
                long long g = divisors[j];

                // Update for pair (i-1, i)
                if (i > 0) {
                    if ((a[i - 1] % g) > (old_val % g)) {
                        counts[j]--;
                    }
                    if ((a[i - 1] % g) > (x % g)) {
                        counts[j]++;
                    }
                }

                // Update for pair (i, i+1)
                if (i < n - 1) {
                    if ((old_val % g) > (a[i + 1] % g)) {
                        counts[j]--;
                    }
                    if ((x % g) > (a[i + 1] % g)) {
                        counts[j]++;
                    }
                }
            }
            a[i] = x;

        } else { // type == 2
            long long k_val;
            std::cin >> k_val;
            
            long long g = std::gcd(k_val, m);
            int idx = div_to_idx[g];
            long long c = counts[idx];

            if (g * c + (a[n - 1] % g) < m) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }
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