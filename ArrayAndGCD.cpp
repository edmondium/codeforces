#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ull = unsigned long long;

// Precompute primes using Sieve of Eratosthenes
vector<int> sieve_primes(int limit) {
    vector<bool> isComposite(limit + 1, false);
    vector<int> primes;
    for (int i = 2; i <= limit; i++) {
        if (!isComposite[i]) {
            primes.push_back(i);
            if ((long long)i * i <= limit) {
                for (int j = i * i; j <= limit; j += i)
                    isComposite[j] = true;
            }
        }
    }
    return primes;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // We might need up to ~400,000 primes.
    // The 400,000th prime is ~6e6. Setting a safe limit:
    const int sieveLimit = 6500000;
    vector<int> primes = sieve_primes(sieveLimit);
    
    // Precompute prefix sums of the primes.
    // primePrefix[i] = sum of the first i primes, with primePrefix[0] = 0.
    vector<ull> primePrefix(primes.size() + 1, 0);
    for (size_t i = 0; i < primes.size(); i++) {
        primePrefix[i + 1] = primePrefix[i] + primes[i];
    }
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<ull> arr(n);
        for (int i = 0; i < n; i++){
            cin >> arr[i];
        }
        
        // The best subset (of size m) to maximize the coin budget is the m largest elements.
        sort(arr.begin(), arr.end(), greater<ull>());
        
        // Compute prefix sums for the sorted array.
        vector<ull> prefix(n + 1, 0);
        for (int i = 0; i < n; i++){
            prefix[i + 1] = prefix[i] + arr[i];
        }
        
        // Find the maximum m (with 1 <= m <= n) such that:
        //     prefix[m] >= primePrefix[m]
        int best = 0;
        // Note: since every a[i] is >= 2, the 1-element case always gives prefix[1] >= 2.
        for (int m = 1; m <= n; m++){
            // It is possible to transform a subset of size m into an ideal array if:
            //     (sum of m largest elements; i.e. prefix[m]) >= (sum of first m primes)
            if (m < (int)primePrefix.size() && prefix[m] >= primePrefix[m])
                best = m;
        }
        
        cout << (n - best) << "\n";
    }
    
    return 0;
}
