#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();

    vector<int> dp(n);
    int maxLength = 0;
    long long count = 0;

    #pragma omp parallel for reduction(max:maxLength) reduction(+:count)
    for (int i = 0; i < n; i++) {
        if (s[i] == ')') {
            int j = i - 1 - (i > 0 ? dp[i - 1] : 0);
            if (j >= 0 && s[j] == '(') {
                dp[i] = dp[i - 1] + 2 + (j > 0 ? dp[j - 1] : 0);
                if (dp[i] > maxLength) {
                    maxLength = dp[i];
                    count = 1;
                } else if (dp[i] == maxLength) {
                    count++;
                }
            }
        }
    }

    if (maxLength == 0) count = 1;
    cout << maxLength << " " << count << "\n";
}
