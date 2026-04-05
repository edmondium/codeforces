#include <bits/stdc++.h>
#include <ranges>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> price(n);
    for (int &p : price) cin >> p;

    unordered_map<string,int> freqMap;
    string name;
    for (int i = 0; i < m; i++) {
        cin >> name;
        freqMap[name]++;
    }

    vector<int> freq;
    transform(freqMap.begin(), freqMap.end(), back_inserter(freq),
              [](auto &kv){ return kv.second; });
    freq.resize(n, 0);

    ranges::sort(price);
    ranges::sort(freq, greater<>());

    long long minCost = 0, maxCost = 0;

    #pragma acc parallel loop reduction(+:minCost)
    for (int i = 0; i < n; i++)
        minCost += 1LL * freq[i] * price[i];

    #pragma acc parallel loop reduction(+:maxCost)
    for (int i = 0; i < n; i++)
        maxCost += 1LL * freq[i] * price[n - 1 - i];

    cout << minCost << " " << maxCost << "\n";
}
