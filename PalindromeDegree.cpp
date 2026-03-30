#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

using ull = unsigned long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> dp(n + 1);
    const ull B = 1315423911ULL;
    ull hf = 0, hr = 0, powB = 1;
    long long answer = 0;

    for (int i = 1; i <= n; i++) {
        unsigned char c = s[i - 1];
        hf = hf * B + c;
        hr = hr + powB * c;
        powB = powB * B;
        dp[i] = (hf == hr) ? dp[i / 2] + 1 : 0;
        answer += dp[i];
    }

    long long total = 0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 1; i <= n; i++) {
        total += dp[i];
    }

    cout << total << "\n";
}
