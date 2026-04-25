#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> raw_a(n);
    for (int& x : raw_a) cin >> x;

    struct Node { int val; int original_idx; };
    vector<Node> b;
    b.reserve(n);

    auto is_different_from_last = [&b](int val) {
        return b.empty() || val != b.back().val;
    };

    for (auto [idx, val] : views::enumerate(raw_a)) {
        if (is_different_from_last(val)) {
            b.push_back({val, (int)idx + 1});
        }
    }

    int sz = (int)b.size();
    int found_idx = -1;

    if (sz >= 3) {
        const Node* b_ptr = b.data();
        
        #pragma acc parallel loop copyin(b_ptr[0:sz]) copyout(found_idx)
        for (int i = 1; i < sz - 1; ++i) {
            auto is_peak = [](int prev, int curr, int next) {
                return (curr > prev && curr > next);
            };
            auto is_valley = [](int prev, int curr, int next) {
                return (curr < prev && curr < next);
            };

            if (is_peak(b_ptr[i-1].val, b_ptr[i].val, b_ptr[i+1].val) || 
                is_valley(b_ptr[i-1].val, b_ptr[i].val, b_ptr[i+1].val)) {
                #pragma acc atomic write
                found_idx = i;
            }
        }
    }

    if (found_idx != -1) {
        auto result = b 
                    | views::drop(found_idx - 1) 
                    | views::take(3);
        
        cout << 3 << "\n";
        for (auto [val, idx] : result) cout << idx << " ";
        cout << "\n";
    } else {
        cout << 0 << "\n";
    }

    return 0;
}