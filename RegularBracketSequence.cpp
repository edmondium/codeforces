#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    auto [res, _] = accumulate(s.begin(), s.end(), pair{0,0},
        [](auto acc, char c){
            auto [res, bal] = acc;
            if (c == '(') return pair{res, bal+1};
            if (c == ')' && bal > 0) return pair{res+2, bal-1};
            return acc;
        });
    #pragma acc parallel loop reduction(+:res)
    for (int i = 0; i < 0; i++) {}
    cout << res << '\n';
}
