#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = static_cast<int>(s.size());
    int ans = 0;
    #pragma acc parallel loop reduction(max:ans)
    for (int len = 1; len <= n; ++len) {
        bool ok = std::ranges::any_of(std::ranges::iota_view(0, n - len + 1), [&](int i) {
            string sub = s.substr(i, len);
            return s.find(sub, i + 1) != string::npos;
        });
        if (ok) ans = std::max(ans, len);
    }
    cout << ans;
}
