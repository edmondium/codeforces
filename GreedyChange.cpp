#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    auto greedyCount = [&](ll x) {
        return accumulate(a.begin(), a.end(), 0LL, [&](ll cnt, ll coin) {
            ll use = x / coin;
            x %= coin;
            return cnt + use;
        });
    };

    ll best = LLONG_MAX;

    #pragma omp parallel for reduction(min:best) schedule(dynamic)
    for (int i = 1; i < n; i++) {
        for (int j = i; j < n; j++) {
            ll need = a[i - 1] - 1;
            ll sum = 0, cnt = 0;
            for (int k = 0; k <= j && need > 0; k++) {
                ll use = need / a[k];
                cnt += use;
                sum += use * a[k];
                need -= use * a[k];
            }
            sum += a[j];
            cnt++;
            ll g = greedyCount(sum);
            if (cnt < g) best = min(best, sum);
        }
    }

    cout << (best == LLONG_MAX ? -1 : best) << "\n";
}
