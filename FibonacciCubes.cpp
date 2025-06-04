#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    // Precompute Fibonacci numbers up to 11 (since n <= 10, we need f[n+1])
    // Using 1-indexing.
    constexpr int MAXF = 11;
    vector<long long> fib(MAXF + 1);
    fib[1] = 1;
    fib[2] = 2;
    for (int i = 3; i <= MAXF; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    while(t--) {
        int n, m;
        cin >> n >> m;
        // For cubes the largest has side fib[n] (since they are ordered by increasing size)
        // And the tiling of a rectangle with squares of side lengths fₙ, fₙ₋₁, …, f₁ exists 
        // in any rectangle of dimensions (at least fₙ) and (at least fₙ₊₁) (with fₙ ≤ fₙ₊₁).
        // We then need one of the three dimensions (vertical) to be at least fib[n] and 
        // the remaining two (the base) to be at least fib[n] and fib[n+1] respectively (in some order).
        string answer;
        answer.resize(m);
        for (int i = 0; i < m; i++) {
            long long d[3];
            cin >> d[0] >> d[1] >> d[2];
            bool good = false;
            // Try every choice for the vertical dimension.
            for (int j = 0; j < 3; j++) {
                long long vertical = d[j];
                vector<long long> base;
                for (int k = 0; k < 3; k++) {
                    if (k == j) continue;
                    base.push_back(d[k]);
                }
                sort(base.begin(), base.end());
                // For a correct tiling we require:
                // vertical >= fib[n] (the largest cube must fit in height)
                // and the two base dimensions (after sorting) satisfy:
                // base[0] >= fib[n] and base[1] >= fib[n+1]
                if (vertical >= fib[n] && base[0] >= fib[n] && base[1] >= fib[n+1]) {
                    good = true;
                    break;
                }
            }
            answer[i] = good ? '1' : '0';
        }
        cout << answer << "\n";
    }

    return 0;
}
