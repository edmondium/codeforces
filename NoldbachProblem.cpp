#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<bool> isPrime(n+1, true);
    isPrime[0] = isPrime[1] = false;
    for (int p = 2; p * p <= n; ++p) {
        if (!isPrime[p]) continue;
        for (int j = p * p; j <= n; j += p)
            isPrime[j] = false;
    }

    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) primes.push_back(i);
    }

    int count = 0;
    for (size_t i = 0; i + 1 < primes.size(); ++i) {
        int s = primes[i] + primes[i+1] + 1;
        if (s <= n && isPrime[s]) {
            count++;
        }
    }

    cout << (count >= k ? "YES\n" : "NO\n");
    return 0;
}
