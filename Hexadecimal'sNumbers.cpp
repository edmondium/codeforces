#include <bits/stdc++.h>
#include <ranges>
#include <omp.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    vector<ll> nums{1};
    ll count = 0;

    while (!nums.empty()) {
        vector<ll> next;
        #pragma omp parallel for reduction(+:count)
        for (size_t i = 0; i < nums.size(); ++i) {
            ll x = nums[i];
            if (x <= n) {
                ++count;
                if (x * 10 <= n) next.push_back(x * 10);
                if (x * 10 + 1 <= n) next.push_back(x * 10 + 1);
            }
        }
        nums = move(next);
    }

    cout << count << "\n";
}
