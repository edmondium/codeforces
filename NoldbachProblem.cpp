#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<bool> isPrime(n+1, true);
    isPrime[0] = isPrime[1] = false;

    int limit = (int)std::sqrt(n);
    #pragma acc parallel loop
    for (int p = 2; p <= limit; ++p) {
        if (isPrime[p]) {
            for (int j = p * p; j <= n; j += p)
                isPrime[j] = false;
        }
    }

    vector<int> primes;
    for (int i : std::views::iota(2, n+1))
        if (isPrime[i]) primes.push_back(i);

    int m = (int)primes.size() - 1;
    int count = 0;
    #pragma acc parallel loop reduction(+:count)
    for (int idx = 0; idx < m; ++idx) {
        int s = primes[idx] + primes[idx+1] + 1;
        if (s <= n && isPrime[s]) count++;
    }

    cout << (count >= k ? "YES\n" : "NO\n");
}
