#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    auto inputs = views::iota(0, t)
        | ranges::views::transform([&](int){ int x; cin >> x; return x; });
    vector<int> n(inputs.begin(), inputs.end()), res(t);
    int* np = n.data();
    int* rp = res.data();
    #pragma acc parallel loop copyin(np[0:t]) copyout(rp[0:t])
    for (int i = 0; i < t; i++) rp[i] = max(0, np[i] - 2);
    auto results = res | ranges::views::transform([](int x){ return x; });
    ranges::for_each(results, [](int x){ cout << x << '\n'; });
}
