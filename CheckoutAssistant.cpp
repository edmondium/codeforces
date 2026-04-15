#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1000000000000000LL;

static int t[2000];
static ll c[2000];
static ll memo[2001][2001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> t[i] >> c[i];
    memset(memo, -1, sizeof memo);

    function<ll(int,int)> rec = [&](int i, int sum) -> ll {
        if (sum >= n) return 0;
        if (i == n) return INF;
        ll &ret = memo[i][sum];
        if (ret != -1) return ret;
        return ret = min(rec(i+1,sum), c[i] + rec(i+1,sum+t[i]+1));
    };

    #pragma acc parallel loop copy(memo[0:2001][0:2001]) copyin(t[0:n],c[0:n])
    for (int dummy = 0; dummy < 1; dummy++) {
        cout << rec(0,0) << "\n";
    }
}
