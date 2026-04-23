#include <bits/stdc++.h>
#include <ranges>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    auto grouped = views::iota(0, n)
        | views::transform([&](int i) {
              return string(1, s[i]) +
                     ((i % 2 && i < n - (n % 2) - 2) ? "-" : "");
          });

    vector<string> parts(grouped.begin(), grouped.end());

    string joined = accumulate(parts.begin(), parts.end(), string{});
    int m = joined.size();
    const char* src = joined.c_str();
    char* out = new char[m+1];

    #pragma acc parallel loop copyin(src[0:m]) copyout(out[0:m])
    for (int i = 0; i < m; i++) {
        out[i] = src[i];
    }
    out[m] = '\0';

    cout << out << '\n';
    delete[] out;
}
