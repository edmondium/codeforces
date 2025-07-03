#include <bits/stdc++.h>
using namespace std;

// Subtract one from a non-negative decimal string (n >= "1")
string decSub1(string s) {
    int i = s.size() - 1;
    while (i >= 0 && s[i] == '0') {
        s[i] = '9';
        --i;
    }
    if (i >= 0) {
        s[i]--;
    }
    // Strip leading zeros if any (e.g. "1000" -> "0999" -> "999")
    if (s[0] == '0' && s.size() > 1)
        s.erase(0, s.find_first_not_of('0'));
    return s;
}

// Fast modular exponentiation (base^exp mod m)
long long modPow(long long base, long long exp, long long m) {
    long long res = 1 % m;
    base %= m;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % m;
        base = (__int128)base * base % m;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string b_str, n_str;
    long long c;
    cin >> b_str >> n_str >> c;

    // 1) b_mod = b % c
    long long b_mod = 0;
    for (char ch : b_str)
        b_mod = (b_mod * 10 + (ch - '0')) % c;

    // 2) (b-1) mod c
    long long b_minus1 = (b_mod + c - 1) % c;

    // 3) exponent = n - 1
    string exp_str = (n_str == "1" ? "0" : decSub1(n_str));

    // 4) precompute b_mod^d for d=0..9
    vector<long long> pow_b(10, 1);
    for (int d = 1; d < 10; ++d)
        pow_b[d] = pow_b[d-1] * b_mod % c;

    // 5) compute b_mod^(n-1) mod c by scanning exp_str
    long long cur = 1;
    for (char ch : exp_str) {
        int d = ch - '0';
        // cur = (cur^10 mod c) * (b^d mod c) % c
        cur = modPow(cur, 10, c) * pow_b[d] % c;
    }

    // 6) total on last page = (b-1)*cur mod c, or c if zero
    long long ans = b_minus1 * cur % c;
    if (ans == 0) ans = c;
    cout << ans << "\n";
    return 0;
}
