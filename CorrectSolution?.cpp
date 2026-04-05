#include <bits/stdc++.h>
#include <ranges>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;

    array<int,10> cnt{};
    for (char c : s) cnt[c - '0']++;

    string minimal;
    if (s == "0") {
        minimal = "0";
    } else {
        int lead = ranges::find_if(views::iota(1,10), [&](int d){ return cnt[d] > 0; })[0];
        minimal.push_back(char('0' + lead));
        cnt[lead]--;

        vector<char> rest;
        #pragma acc parallel loop copyin(cnt)
        for (int d = 0; d <= 9; d++) {
            rest.insert(rest.end(), cnt[d], char('0' + d));
        }
        minimal.append(rest.begin(), rest.end());
    }

    cout << (t == minimal ? "OK\n" : "WRONG_ANSWER\n");
}
