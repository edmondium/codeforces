#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n): n(_n), f(n+1, 0) {}
    void update(int i, int v) {
        for(; i <= n; i += i & -i) f[i] = max(f[i], v);
    }
    int query(int i) const {
        int r = 0;
        for(; i > 0; i -= i & -i) r = max(r, f[i]);
        return r;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; 
    cin >> N;
    vector<int> B(N), I(N), R(N);
    for_each(B.begin(), B.end(), [&](int &x){ cin >> x; });
    for_each(I.begin(), I.end(), [&](int &x){ cin >> x; });
    for_each(R.begin(), R.end(), [&](int &x){ cin >> x; });

    vector<int> coords = I;
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    auto getCI = [&](int x){
        int pos = int(lower_bound(coords.begin(), coords.end(), x) - coords.begin()) + 1;
        return int(coords.size()) - pos + 1;
    };
    int M = coords.size();

    vector<int> pts(N);
    iota(pts.begin(), pts.end(), 0);
    sort(pts.begin(), pts.end(), [&](int a, int b){ return B[a] > B[b]; });

    Fenwick ft(M);
    long long dominated = 0;

    for(int i = 0; i < N; ) {
        int j = i;
        while(j < N && B[pts[j]] == B[pts[i]]) ++j;
        for_each(pts.begin()+i, pts.begin()+j, [&](int p){
            int ci = getCI(I[p]);
            int maxR = ft.query(ci - 1);
            if(maxR > R[p]) dominated++;
        });
        for_each(pts.begin()+i, pts.begin()+j, [&](int p){
            int ci = getCI(I[p]);
            ft.update(ci, R[p]);
        });
        i = j;
    }

    cout << dominated << "\n";
}
