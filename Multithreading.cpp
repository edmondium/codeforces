#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;
struct Proc { int id, v; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; long long w;
    cin >> n >> w;
    vector<Proc> a(n);
    long long tot = 0;
    for (int i=0;i<n;i++) { cin >> a[i].v; a[i].id=i+1; tot+=a[i].v; }
    ranges::sort(a, {}, &Proc::v);

    auto print_seq = [&](auto seq) {
        for (int x : seq) cout << x << " ";
        cout << "\n";
    };

    if (n==1 && w==tot) {
        cout<<"Yes\n";
        auto seq = views::iota(0,2*a[0].v) | views::transform([&](int){return a[0].id;});
        print_seq(seq);
        return 0;
    }
    if (n>=2 && w>=2 && w<=tot) {
        cout<<"Yes\n";
        vector<int> out;
        while (w>2) {
            if (a[0].v>1) { a[0].v--; out.insert(out.end(),{a[0].id,a[0].id}); w--; }
            else if (a.back().v) { a.back().v--; out.insert(out.end(),{a.back().id,a.back().id}); w--; }
            else a.pop_back();
        }
        if (a[1].v) {
            a[1].v--; a[0].v--;
            out.push_back(a[0].id);
            for (int i=1;i<n;i++)
                ranges::for_each(views::iota(0,a[i].v),[&](int){out.insert(out.end(),{a[i].id,a[i].id});});
            out.push_back(a[0].id);
            out.push_back(a[1].id);
            ranges::for_each(views::iota(0,a[0].v),[&](int){out.insert(out.end(),{a[0].id,a[0].id});});
            out.push_back(a[1].id);
        } else out.insert(out.end(),{a[0].id,a[0].id});
        #pragma acc parallel loop
        for (int i=0;i<(int)out.size();i++) cout<<out[i]<<" ";
        cout<<"\n";
        return 0;
    }
    if (n>=2 && w==1 && a[0].v==1) {
        cout<<"Yes\n";
        vector<int> out{a[0].id};
        for (int i=1;i<n;i++)
            ranges::for_each(views::iota(0,a[i].v),[&](int){out.insert(out.end(),{a[i].id,a[i].id});});
        out.push_back(a[0].id);
        #pragma acc parallel loop
        for (int i=0;i<(int)out.size();i++) cout<<out[i]<<" ";
        cout<<"\n";
        return 0;
    }
    cout<<"No\n";
}
