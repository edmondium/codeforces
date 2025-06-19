#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <ctime>
using namespace std;

const int MAXN = 50;

typedef long long ll;

int n, nPrefix;
ll rem;
int s[MAXN];

ll dp[MAXN + 1][2][2];

ll f(int pos, int less, int lessRev) {
    if (dp[pos][less][lessRev] != -1) return dp[pos][less][lessRev];
    if (pos >= n) {
        if (less && lessRev) {
            dp[pos][less][lessRev] = 1;
            return 1;
        }
        else {
            dp[pos][less][lessRev] = 0;
            return 0;
        }
    }
    ll ret = 0;
    for (int i = 0; i <= 1; ++i) {
        int nextLess = less;
        int nextLessRev = lessRev;
        if (i > s[n - 1 - pos]) {
            nextLess = 1;
        }
        else if (i < s[n - 1 - pos]) {
            nextLess = 0;
        }
        if (1 - i > s[n - 1 - pos]) {
            nextLessRev = 1;
        }
        if (1 - i < s[n - 1 - pos]) {
            nextLessRev = 0;
        }
        ret += f(pos + 1, nextLess, nextLessRev);
    }
    dp[pos][less][lessRev] = ret;
    return ret;
}

int main() {
    cin >> n >> rem;
    ++rem;
    nPrefix = n / 2 + n % 2;
    bool found = false;
    int prefix;
    memset(dp, -1, sizeof dp);
    memset(s, 0, sizeof s);
    for (prefix = 0; prefix < (1 << nPrefix); ++prefix) {
        if (prefix > 0) {
            int i = nPrefix - 1;
            while (i >= 0) {
                if (s[i] == 0) {
                    s[i] = 1;
                    break;
                }
                s[i] = 0;
                --i;
            }
            for (int j = n - nPrefix; j <= n - 1 - i; ++j) {
                dp[j][0][0] = -1;
                dp[j][0][1] = -1;
                dp[j][1][0] = -1;
                dp[j][1][1] = -1;
            }
        }
        int firstPos = nPrefix;
        int less = 1;
        int lessRev = 1;
        if (n % 2 == 1 && s[nPrefix - 1] == 1) lessRev = 0;
        ll temp = f(firstPos, less, lessRev);
        if (temp < rem) {
            rem -= temp;
        }
        else {
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "-1" << endl;
        return 0;
    }
    int less = 1, lessRev = 1;
    if (n % 2 == 1 && s[nPrefix - 1] == 1) lessRev = 0;
    for (int pos = nPrefix; pos < n; ++pos) {
        int nextLess = less;
        int nextLessRev = lessRev;
        if (0 < s[n - 1 - pos]) nextLess = 0;
        if (1 > s[n - 1 - pos]) nextLessRev = 1;
        ll temp = f(pos + 1, nextLess, nextLessRev);
        if (temp >= rem) {
            s[pos] = 0;
            less = nextLess;
            lessRev = nextLessRev;
            continue;
        }
        rem -= temp;
        s[pos] = 1;
        if (1 > s[n - 1 - pos]) less = 1;
        if (0 < s[n - 1 - pos]) lessRev = 0;
    }
    for (int i = 0; i < n; ++i) {
        cout << s[i];
    }
    cout << endl;
    return 0;
}