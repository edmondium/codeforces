#include <iostream>
#include <vector>
#include <numeric>

// It's good practice to put precomputation outside main if it's constant.
const int MAXN = 100000;
std::vector<int> lpf(MAXN + 1, 0); // Stores the Largest Prime Factor for each number
std::vector<int> primes;

// This function performs the precomputation.
void sieve() {
    // This Sieve correctly computes the Largest Prime Factor (LPF) for every
    // number up to MAXN. It also populates a list of prime numbers.
    for (int i = 2; i <= MAXN; ++i) {
        if (lpf[i] == 0) {
            // If lpf[i] is 0, it means i is a prime number because it wasn't
            // divided by any smaller prime.
            lpf[i] = i; // The LPF of a prime is itself.
            primes.push_back(i);
        }
        // Iterate through primes smaller than or equal to the LPF of i.
        // This efficiently marks the multiples.
        for (int p : primes) {
            if (p > lpf[i] || (long long)i * p > MAXN) {
                break;
            }
            lpf[i * p] = p;
        }
    }
}


void solve() {
    int n;
    std::cin >> n;

    // The core logic of your solution is sound, but it depends on the correct
    // prime factorization, which the corrected sieve now provides.

    // 1) Bucket indices by their largest prime factor.
    // We use a vector of vectors to group numbers.
    std::vector<std::vector<int>> groups(n + 1);
    for (int i = 2; i <= n; ++i) {
        // Find the largest prime factor of i by repeatedly dividing i by its smallest prime factor.
        int temp = i;
        int largest_prime_factor = 0;
        while (temp > 1) {
            int current_prime = lpf[temp];
            largest_prime_factor = std::max(largest_prime_factor, current_prime);
            while (temp % current_prime == 0) {
                temp /= current_prime;
            }
        }
        if (largest_prime_factor > 0) {
            groups[largest_prime_factor].push_back(i);
        }
    }


    // 2) Build the permutation.
    std::vector<int> p(n + 1);
    std::vector<bool> assigned(n + 1, false);
    p[1] = 1;
    assigned[1] = true;

    // Iterate through numbers and form cycles within their LPF groups.
    for (int i = 2; i <= n; ++i) {
        if (!assigned[i]) {
            int temp = i;
            int largest_prime_factor = 0;
            while (temp > 1) {
                int current_prime = lpf[temp];
                largest_prime_factor = std::max(largest_prime_factor, current_prime);
                while (temp % current_prime == 0) {
                    temp /= current_prime;
                }
            }
            
            auto& G = groups[largest_prime_factor];
            if (G.size() <= 1) {
                // This case handles numbers that are unique for their LPF (e.g., large primes).
                // This creates a necessary fixed point.
                p[i] = i;
                assigned[i] = true;
            } else {
                // Create one big cycle to avoid fixed points within the group.
                for (size_t j = 0; j < G.size(); ++j) {
                    p[G[j]] = G[(j + 1) % G.size()];
                    assigned[G[j]] = true;
                }
            }
        }
    }


    // 3) Output the resulting permutation.
    for (int i = 1; i <= n; ++i) {
        std::cout << p[i] << (i == n ? "" : " ");
    }
    std::cout << "\n";
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Perform precomputation once before handling test cases.
    sieve();

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
