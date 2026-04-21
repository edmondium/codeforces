#include <bits/stdc++.h>
#include <ranges>
using namespace std;
struct Item { long long a,o; int id; };

template <typename R, typename F>
auto sum_range(R&& r, F f) {
    return accumulate(r.begin(), r.end(), 0LL,
        [&](long long acc, auto&& x){ return acc + f(x); });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<Item> v(2*n-1);
        for (int i=0;i<2*n-1;i++) {
            cin >> v[i].a >> v[i].o;
            v[i].id=i+1;
        }
        ranges::sort(v,{},&Item::a);
        auto totA = sum_range(v,[](auto& it){return it.a;});
        auto totO = sum_range(v,[](auto& it){return it.o;});
        auto oddA = sum_range(v | ranges::views::drop(1) | ranges::views::stride(2),[](auto& it){return it.a;}) + v.back().a;
        auto oddO = sum_range(v | ranges::views::drop(1) | ranges::views::stride(2),[](auto& it){return it.o;}) + v.back().o;
        auto evenA = sum_range(v | ranges::views::stride(2),[](auto& it){return it.a;});
        auto evenO = sum_range(v | ranges::views::stride(2),[](auto& it){return it.o;});
        vector<int> choice;
        if (2*oddA>=totA && 2*oddO>=totO) {
            for (int i=1;i<2*n-1;i+=2) choice.push_back(v[i].id);
            choice.push_back(v.back().id);
        } else if (2*evenA>=totA && 2*evenO>=totO) {
            for (int i=0;i<2*n-1;i+=2) choice.push_back(v[i].id);
        }
        if (!choice.empty()) {
            cout<<"YES\n";
            for (int x:choice) cout<<x<<" ";
            cout<<"\n";
        } else cout<<"NO\n";
    }
}
