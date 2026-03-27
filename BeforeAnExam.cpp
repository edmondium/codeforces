#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <execution>
#include <ranges>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d, sumTime;
    cin >> d >> sumTime;
    vector<int> minTime(d), maxTime(d);

    for (int i = 0; i < d; i++) cin >> minTime[i] >> maxTime[i];

    int totalMin = 0, totalMax = 0;

    #pragma omp parallel for reduction(+:totalMin,totalMax)
    for (int i = 0; i < d; i++) {
        totalMin += minTime[i];
        totalMax += maxTime[i];
    }

    if (sumTime < totalMin || sumTime > totalMax) {
        cout << "NO\n";
        return 0;
    }

    vector<int> schedule = minTime;
    int extra = sumTime - totalMin;

    for (int i = 0; i < d && extra > 0; i++) {
        int add = min(extra, maxTime[i] - minTime[i]);
        schedule[i] += add;
        extra -= add;
    }

    cout << "YES\n";
    ranges::for_each(schedule | views::enumerate, [&](auto&& p) {
        auto [i, val] = p;
        cout << val << (i + 1 < d ? " " : "\n");
    });

    return 0;
}
