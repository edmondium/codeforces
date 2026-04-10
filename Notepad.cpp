#include <bits/stdc++.h>
using namespace std;

auto decSub1 = [](string s) {
    int i = (int)s.size() - 1;
    while (i >= 0 && s[i] == '0') { s[i] = '9'; --i; }
    if (i >= 0) s[i]--;
    if (s[0] == '0' && s.size() > 1) s.erase(0, s.find_first_not_of('0'));
    return s;
};

auto modPow = [](long long base, long long exp, long long m) {
    long long res = 1 % m;
    base %= m;
    while (exp > 0) {
        if (exp & 1) res = (__int128)res * base % m;
        base = (__int128)base * base % m;
        exp >>= 1;
    }
    return res;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string b_str, n_str;
    long long c;
    cin >> b_str >> n_str >> c;

    long long b_mod = accumulate(b_str.begin(), b_str.end(), 0LL,
        [&](long long acc, char ch){ return (acc * 10 + (ch - '0')) % c; });

    long long b_minus1 = (b_mod + c - 1) % c;
    string exp_str = (n_str == "1" ? "0" : decSub1(n_str));

    vector<long long> pow_b(10, 1);
    for (int d = 1; d < 10; ++d) pow_b[d] = pow_b[d-1] * b_mod % c;

    long long cur = 1;
    #pragma acc parallel loop reduction(*:cur)
    for (int i = 0; i < (int)exp_str.size(); ++i) {
        int d = exp_str[i] - '0';
        cur = modPow(cur, 10, c) * pow_b[d] % c;
    }

    long long ans = b_minus1 * cur % c;
    if (ans == 0) ans = c;
    cout << ans << "\n";
}
