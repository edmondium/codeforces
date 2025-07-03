#include <bits/stdc++.h>
using namespace std;

static const int MOD = 51123987;

int add(int a, int b) { 
    a += b; 
    if (a >= MOD) a -= MOD; 
    return a; 
}

int subm(int a, int b) { 
    a -= b; 
    if (a < 0) a += MOD; 
    return a; 
}

int mul(long long a, long long b) { 
    return int((a * b) % MOD); 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    vector<int> d1(n), d2(n);

    // Manacher’s for odd-length palindromes
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r ? 1 : min(d1[l + r - i], r - i + 1));
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    // Manacher’s for even-length palindromes
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1));
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }

    // Difference arrays to accumulate start/end counts
    vector<int> startDiff(n + 2, 0), endDiff(n + 2, 0);

    for (int idx = 1; idx <= n; idx++) {
        int i = idx - 1;

        // odd palindromes: corrected start index
        int l = idx - d1[i] + 1;
        int r = idx + d1[i] - 1;
        startDiff[l]       = add(startDiff[l], 1);
        startDiff[idx + 1] = subm(startDiff[idx + 1], 1);
        endDiff[idx]       = add(endDiff[idx], 1);
        endDiff[r + 1]     = subm(endDiff[r + 1], 1);

        // even palindromes
        if (d2[i] > 0) {
            l = idx - d2[i];
            r = idx + d2[i] - 1;
            startDiff[l]   = add(startDiff[l], 1);
            startDiff[idx] = subm(startDiff[idx], 1);
            endDiff[idx]   = add(endDiff[idx], 1);
            endDiff[r + 1] = subm(endDiff[r + 1], 1);
        }
    }

    vector<int> startCount(n + 2, 0), endCount(n + 2, 0);
    long long totalPals = 0;

    for (int i = 1; i <= n; i++) {
        startCount[i] = add(startCount[i - 1], startDiff[i]);
        endCount[i]   = add(endCount[i - 1], endDiff[i]);
        totalPals     = (totalPals + startCount[i]) % MOD;
    }

    // total unordered pairs of palindromes
    int totalPairs = mul(totalPals, (totalPals - 1 + MOD) % MOD);
    totalPairs     = mul(totalPairs, (MOD + 1) / 2);

    // suffix sums of startCount
    vector<int> suffixStart(n + 3, 0);
    for (int i = n; i >= 1; i--) {
        suffixStart[i] = add(startCount[i], suffixStart[i + 1]);
    }

    // count disjoint pairs
    int disj = 0;
    for (int j = 1; j < n; j++) {
        disj = add(disj, mul(endCount[j], suffixStart[j + 1]));
    }

    // answer = totalPairs − disjoint
    int answer = subm(totalPairs, disj);
    cout << answer << "\n";

    return 0;
}
