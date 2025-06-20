#include <iostream>
#include <vector>

/**
 * Calculates the digital root of a positive integer n.
 * This is equivalent to (n-1) % 9 + 1.
 */
long long digital_root(long long n) {
    long long root = n % 9;
    if (root == 0) {
        return 9;
    }
    return root;
}

/**
 * Solves the Digital Root problem.
 */
void solve() {
    long long n;
    std::cin >> n;

    // 1. Count how many numbers from 1 to N have each possible digital root (1-9).
    std::vector<long long> count_dr(10, 0);
    for (int k = 1; k <= 9; ++k) {
        if (n >= k) {
            count_dr[k] = (n - k) / 9 + 1;
        }
    }

    // 2. Calculate the total number of triples (A,B,C) for which Billy's check passes.
    long long count_billy_ok = 0;
    for (int i = 1; i <= 9; ++i) { // i is the digital root of A
        for (int j = 1; j <= 9; ++j) { // j is the digital root of B
            long long k = digital_root(i * j); // k is the required digital root of C
            // The number of such triples is the product of the counts for each digital root.
            count_billy_ok += count_dr[i] * count_dr[j] * count_dr[k];
        }
    }

    // 3. Calculate the total number of triples where A*B=C (and A,B,C <= N).
    // This is equivalent to counting pairs (A,B) where A*B <= N.
    long long count_correct = 0;
    for (long long a = 1; a <= n; ++a) {
        count_correct += n / a;
    }

    // 4. The number of mistakes is the difference.
    long long mistakes = count_billy_ok - count_correct;
    std::cout << mistakes << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    solve();
    return 0;
}