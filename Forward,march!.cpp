#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

auto eval = [](const string &s) {
    int good = 0, total = 0, flipFlag = 0, skips = 0;
    for (char ch : s) {
        if (ch == 'X') total++;
        else if (ch == (total % 2 ? 'R' : 'L')) { good++; total++; flipFlag = 0; }
        else { good++; total += 2; skips += flipFlag; flipFlag = !flipFlag; }
    }
    if (total % 2) { total++; skips += flipFlag; }
    if (good * 2 > total) { good -= skips; total -= skips * 2; }
    return double(good) / total;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    string t; t.reserve(s.size() * 2);
    for (size_t i = 0; i + 1 < s.size(); ++i) {
        t.push_back(s[i]);
        if (s[i] != 'X' && s[i] == s[i+1]) t.push_back('X');
    }
    if (!s.empty()) t.push_back(s.back());

    double ans = 0.0;
    if (!t.empty() && t.front() == t.back() && t.front() != 'X') {
        double res1, res2;
        #pragma omp parallel sections
        {
            #pragma omp section
            { res1 = eval("X" + t); }
            #pragma omp section
            { res2 = eval(t + "X"); }
        }
        ans = max(res1, res2);
    } else ans = eval(t);

    ans = floor(ans * 1e8) / 1e6;
    cout << fixed << setprecision(6) << ans << "\n";
}
