#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int MOD = 1'000'000'007;
const int MAXA = 100000;

int64 mod_pow(int64 a, int64 e = MOD - 2) {
    int64 r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute factorials and inverse factorials up to MAXA
    static int64 fact[MAXA + 1], inv_fact[MAXA + 1];
    fact[0] = 1;
    for (int i = 1; i <= MAXA; i++)
        fact[i] = fact[i - 1] * i % MOD;
    inv_fact[MAXA] = mod_pow(fact[MAXA]);
    for (int i = MAXA; i > 0; i--)
        inv_fact[i - 1] = inv_fact[i] * i % MOD;

    int T;
    cin >> T;
    while (T--) {
        int a, b, k;
        cin >> a >> b >> k;

        // Compute n = k*(a-1) + 1  (mod MOD)
        int64 n_real = int64(k) * (a - 1) + 1;
        int64 n_mod  = n_real % MOD;

        // Compute C(n, a) mod MOD using Lucas + direct product for small a
        int64 Cna = 0;
        // By Lucas: if n_mod < a, then C(n,a) ≡ 0 (mod MOD)
        if (n_mod >= a) {
            // numerator = n_mod * (n_mod - 1) * ... * (n_mod - (a-1))
            int64 num = 1;
            for (int i = 0; i < a; i++) {
                num = num * ((n_mod - i + MOD) % MOD) % MOD;
            }
            // divide by a! via inv_fact
            Cna = num * inv_fact[a] % MOD;
        }

        // Compute m = (b-1)*k*Cna + 1  (mod MOD)
        int64 m_mod = ( (int64(b - 1 + MOD) % MOD) * (k % MOD) % MOD * Cna % MOD + 1 ) % MOD;

        cout << n_mod << " " << m_mod << "\n";
    }

    return 0;
}
