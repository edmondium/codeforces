#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    string out;
    out.reserve(n);

    const char* arr = s.c_str();

    #pragma acc parallel loop copyin(arr[0:n]) copy(out)
    for (int i = 0; i < n; ++i) {
        if (arr[i] == '/' && !out.empty() && out.back() == '/') continue;
        out.push_back(arr[i]);
    }

    if (out.size() > 1 && out.back() == '/') out.pop_back();
    cout << out << '\n';
}
