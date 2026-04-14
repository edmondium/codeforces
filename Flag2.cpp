#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (auto &row : a) cin >> row;
    vector<vector<int>> cost(n, vector<int>(26 * 26, 1e9));
    vector<vector<int>> parent(n, vector<int>(26 * 26, -1));
    #pragma acc parallel loop
    for (int i = 0; i < n; i++) {
        for (int c1 = 0; c1 < 26; c1++) {
            for (int c2 = 0; c2 < 26; c2++) {
                if (c1 == c2) continue;
                int idx = c1 * 26 + c2;
                int repaint = 0;
                for (int j = 0; j < m; j++) {
                    char expected = (j % 2 == 0 ? 'a' + c1 : 'a' + c2);
                    if (a[i][j] != expected) repaint++;
                }
                cost[i][idx] = repaint;
            }
        }
    }
    vector<vector<int>> dp(n, vector<int>(26 * 26, 1e9));
    for (int idx = 0; idx < 26 * 26; idx++) dp[0][idx] = cost[0][idx];
    for (int i = 1; i < n; i++) {
        #pragma acc parallel loop
        for (int idx = 0; idx < 26 * 26; idx++) {
            for (int prev = 0; prev < 26 * 26; prev++) {
                if (idx / 26 == prev / 26 || idx % 26 == prev % 26) continue;
                int val = dp[i - 1][prev] + cost[i][idx];
                if (val < dp[i][idx]) {
                    dp[i][idx] = val;
                    parent[i][idx] = prev;
                }
            }
        }
    }
    int best = min_element(dp[n - 1].begin(), dp[n - 1].end()) - dp[n - 1].begin();
    cout << dp[n - 1][best] << "\n";
    vector<string> res(n);
    for (int i = n - 1, cur = best; i >= 0; i--) {
        int c1 = cur / 26, c2 = cur % 26;
        res[i].resize(m);
        #pragma acc parallel loop
        for (int j = 0; j < m; j++) res[i][j] = (j % 2 == 0 ? 'a' + c1 : 'a' + c2);
        cur = parent[i][cur];
    }
    for (auto &row : res) cout << row << "\n";
}
