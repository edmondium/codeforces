#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <string_view>
#include <openacc.h>

using namespace std;

typedef long long ll;
const ll MOD1 = 1e9 + 7, MOD2 = 1e9 + 9, B1 = 131, B2 = 137;

struct HashStr {
    vector<ll> h1, h2, p1, p2;
    HashStr(string_view s) {
        int n = s.size();
        h1.resize(n + 1, 0); h2.resize(n + 1, 0);
        p1.resize(n + 1, 1); p2.resize(n + 1, 1);
        
        ll* d_h1 = h1.data(); ll* d_h2 = h2.data();
        ll* d_p1 = p1.data(); ll* d_p2 = p2.data();
        const char* d_s = s.data();

        #pragma acc parallel loop copyin(d_s[0:n]) copy(d_h1[0:n+1], d_h2[0:n+1], d_p1[0:n+1], d_p2[0:n+1])
        for (int i = 0; i < n; i++) {
            d_h1[i + 1] = (d_h1[i] * B1 + d_s[i]) % MOD1;
            d_h2[i + 1] = (d_h2[i] * B2 + d_s[i]) % MOD2;
            d_p1[i + 1] = (d_p1[i] * B1) % MOD1;
            d_p2[i + 1] = (d_p2[i] * B2) % MOD2;
        }
    }
    pair<ll, ll> get(int l, int r) const {
        return {(h1[r] - h1[l] * p1[r - l] % MOD1 + MOD1) % MOD1,
                (h2[r] - h2[l] * p2[r - l] % MOD2 + MOD2) % MOD2};
    }
};

auto get_merge = [](string_view a, string_view b) -> string {
    HashStr ha(a), hb(b);
    auto is_sub = [&]() {
        if (b.size() > a.size()) return false;
        auto target = hb.get(0, b.size());
        auto r = views::iota(0, (int)(a.size() - b.size() + 1));
        return any_of(r.begin(), r.end(), [&](int i) { return ha.get(i, i + b.size()) == target; });
    };

    if (is_sub()) return string(a);
    
    auto overlap = views::iota(1, (int)min(a.size(), b.size()) + 1) 
                 | views::reverse 
                 | views::filter([&](int len) {
                       return ha.get(a.size() - len, a.size()) == hb.get(0, len);
                   }) 
                 | views::take(1);

    int len = overlap.empty() ? 0 : *overlap.begin();
    return string(a) + string(b.substr(len));
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> s(3);
    while (cin >> s[0] >> s[1] >> s[2]) {
        vector<int> indices = {0, 1, 2};
        vector<vector<int>> perms;
        do { perms.push_back(indices); } while (next_permutation(indices.begin(), indices.end()));

        auto results = perms | views::transform([&](const auto& p) {
            return get_merge(get_merge(s[p[0]], s[p[1]]), s[p[2]]).size();
        });

        cout << ranges::fold_left(results, size_t(-1), [](size_t a, size_t b) { 
            return min(a, b); 
        }) << "\n";
    }
    return 0;
}