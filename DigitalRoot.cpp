#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

auto digital_root = [](long long n) {
    auto r = n % 9;
    return r == 0 ? 9 : r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    vector<long long> count_dr(10);
    ranges::for_each(views::iota(1, 10), [&](int k) {
        if (n >= k) count_dr[k] = (n - k) / 9 + 1;
    });

    long long count_billy_ok = 0;
    #pragma omp parallel for reduction(+:count_billy_ok)
    for (int i = 1; i <= 9; ++i)
        for (int j = 1; j <= 9; ++j) {
            auto k = digital_root(i * j);
            count_billy_ok += count_dr[i] * count_dr[j] * count_dr[k];
        }

    long long count_correct = 0;
    #pragma omp parallel for reduction(+:count_correct)
    for (long long a = 1; a <= n; ++a)
        count_correct += n / a;

    cout << count_billy_ok - count_correct << '\n';
}
