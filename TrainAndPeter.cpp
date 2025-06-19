#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string T, A, B;
    cin >> T >> A >> B;

    auto check = [&](const string &S) {
        size_t p1 = S.find(A);
        if (p1 == string::npos) return false;
        size_t p2 = S.find(B, p1 + A.size());
        return p2 != string::npos;
    };

    bool fwd = check(T);
    reverse(T.begin(), T.end());
    bool bwd = check(T);

    if (fwd && bwd)      cout << "both\n";
    else if (fwd)        cout << "forward\n";
    else if (bwd)        cout << "backward\n";
    else                 cout << "fantasy\n";

    return 0;
}
