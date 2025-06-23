#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// Evaluate the max-correct fraction for a fixed sequence s (with breaks already inserted)
double eval(const string &s) {
    int good = 0;     // matched steps
    int total = 0;    // total time slots
    int flipFlag = 0; // toggles when we “skip” a duplicate
    int skips = 0;    // count of extra skips we inserted in eval

    for (char ch : s) {
        if (ch == 'X') {
            // explicit break
            total++;
        }
        else if (ch == (total % 2 ? 'R' : 'L')) {
            // correct foot for this parity
            good++;
            total++;
            flipFlag = 0;
        }
        else {
            // wrong foot—force a double‐skip: “X” + this step
            good++;
            total += 2;
            skips += flipFlag;
            flipFlag = !flipFlag;
        }
    }

    // If we end on odd parity, we can optionally append a break
    if (total % 2) {
        total++;
        skips += flipFlag;
    }

    // If we matched more than half, we can remove some of the skip‐pairs
    if (good * 2 > total) {
        good   -= skips;
        total  -= skips * 2;
    }

    return double(good) / total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    // Pre‐insert one break between any LL or RR
    string t;
    t.reserve(s.size() * 2);
    for (size_t i = 0; i + 1 < s.size(); ++i) {
        t.push_back(s[i]);
        if (s[i] != 'X' && s[i] == s[i+1])
            t.push_back('X');
    }
    if (!s.empty())
        t.push_back(s.back());

    // Try optionally adding an X at front or back if endpoints collide
    double ans;
    if (!t.empty() && t.front() == t.back() && t.front() != 'X') {
        ans = max(
            eval(string("X") + t),
            eval(t + "X")
        );
    }
    else {
        ans = eval(t);
    }

    // Round down to 6 decimals and print as a percent
    ans = floor(ans * 1e8) / 1e6;
    cout << fixed << setprecision(6) << ans << "\n";
    return 0;
}
