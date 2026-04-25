#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <limits>
#include <openacc.h>

using ull = unsigned long long;

int main() {
    ull n;
    if (!(std::cin >> n)) return 0;

    if (n == 1) {
        std::cout << 1 << std::endl;
        return 0;
    }

    const ull primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    const ull inf = 2e18;
    ull final_min = inf;

    auto solve_recursive = [&](auto&& self, int depth, ull current_n, ull current_val) -> ull {
        if (current_n == n) return current_val;
        if (depth >= 15) return inf;

        ull local_min = inf;
        for (int i = 1; i < 64; ++i) {
            ull next_val = current_val;
            bool overflow = false;
            for (int j = 0; j < i; ++j) {
                if (inf / primes[depth] < next_val) {
                    overflow = true;
                    break;
                }
                next_val *= primes[depth];
            }
            if (overflow) break;

            if (n % (current_n * (i + 1)) == 0) {
                ull res = self(self, depth + 1, current_n * (i + 1), next_val);
                if (res < local_min) local_min = res;
            }
        }
        return local_min;
    };

    #pragma acc parallel loop copyin(primes[:15]) reduction(min:final_min)
    for (int i = 1; i < 64; ++i) {
        ull val = 1;
        bool overflow = false;
        for (int j = 0; j < i; ++j) {
            if (inf / primes[0] < val) {
                overflow = true;
                break;
            }
            val *= primes[0];
        }

        if (!overflow && n % (i + 1) == 0) {
            ull res = solve_recursive(solve_recursive, 1, (ull)i + 1, val);
            if (res < final_min) final_min = res;
        }
    }

    std::cout << final_min << std::endl;

    return 0;
}