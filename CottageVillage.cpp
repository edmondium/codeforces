#include <bits/stdc++.h>
#include <ranges>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    vector<pair<int,int>> H(n);
    for (auto& [x,a] : H) {
        cin >> x >> a;
        x *= 2;
    }
    t *= 2;

    ranges::sort(H);

    int ans = 2;
    #pragma acc parallel loop reduction(+:ans)
    for (int i = 0; i < n - 1; i++) {
        int right_i = H[i].first + H[i].second;
        int left_j  = H[i+1].first - H[i+1].second;
        int gap = left_j - right_i;
        if (gap == t) ans += 1;
        else if (gap > t) ans += 2;
    }

    cout << ans << '\n';
}
