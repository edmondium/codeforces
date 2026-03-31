#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string T, A, B;
    cin >> T >> A >> B;

    auto check = [&](const string &S) {
        return [&] {
            size_t p1 = S.find(A);
            return p1 != string::npos && S.find(B, p1 + A.size()) != string::npos;
        }();
    };

    bool fwd = false, bwd = false;

    #pragma omp parallel sections
    {
        #pragma omp section
        { fwd = check(T); }
        #pragma omp section
        { string R = T; reverse(R.begin(), R.end()); bwd = check(R); }
    }

    cout << (fwd && bwd ? "both" : fwd ? "forward" : bwd ? "backward" : "fantasy") << '\n';
}
