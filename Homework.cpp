#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
using ulll = unsigned __int128;

constexpr ull inf = 0x3f3f3f3f3f3f3f3f;
constexpr ull mod = 1e9 + 7;
constexpr ull N = 1000;
constexpr ull M = 1e6;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        string s, t;
        cin >> s >> t;

        int l = n >> __builtin_ctz(n);

        if (l < 1000) {
            auto solve = [&](const string& s) {
                vector<bitset<N>> h(l);
                auto add = [&](bitset<N> b) {
                    for (int i = 0; i < l; i++) {
                        if (b.test(i)) {
                            if (h[i].none()) {
                                for (int j = i + 1; j < l; j++) {
                                    if (!h[j].none() && b.test(j)) {
                                        b ^= h[j];
                                    }
                                }
                                for (int j = 0; j < i; j++) {
                                    if (!h[j].none() && h[j].test(i)) {
                                        h[j] ^= b;
                                    }
                                }
                                h[i] = b;
                                return;
                            }
                            b ^= h[i];
                        }
                    }
                };
                for (int i = 0; i < n; i += l) {
                    bitset<N> b(s.substr(i, l));
                    add(b);
                }
                return h;
            };
            if (solve(s) == solve(t)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        } else {
            auto solve = [&](const string& s) {
                map<int, bitset<M>> h;  
                auto add = [&](bitset<M> b) {
                    for (int i = 0; i < l; i++) {
                        if (b.test(i)) {
                            if (h[i].none()) {
                                for (int j = i + 1; j < l; j++) {
                                    if (h.count(j) && b.test(j)) {
                                        b ^= h[j];
                                    }
                                }
                                for (int j = 0; j < i; j++) {
                                    if (h.count(j) && h[j].test(i)) {
                                        h[j] ^= b;
                                    }
                                }
                                h[i] = b;
                                return;
                            }
                            b ^= h[i];
                        }
                    }
                };
                for (int i = 0; i < n; i += l) {
                    bitset<M> b(s.substr(i, l));
                    add(b);
                }
                return h;
            };
            if (solve(s) == solve(t)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}