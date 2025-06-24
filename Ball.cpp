#include <bits/stdc++.h>
using namespace std;

// Fenwick for range‐max on [1..n]
struct Fenwick {
    int n;
    vector<int> f;
    Fenwick(int _n): n(_n), f(n+1, 0) {}
    // update position i to max(f[i], v)
    void update(int i, int v) {
        for(; i <= n; i += i & -i)
            f[i] = max(f[i], v);
    }
    // query max in [1..i]
    int query(int i) const {
        int r = 0;
        for(; i > 0; i -= i & -i)
            r = max(r, f[i]);
        return r;
    }
    // query max in [l..r]
    int query_range(int l, int r) const {
        if(l > r) return 0;
        // We can't directly do range‐max with prefix Fenwick,
        // so invert coordinates and re­build or maintain a suffix‐Fenwick.
        // Simpler: store reversed indices on I so that a prefix‐max is actually I>xi.
        // In this code we'll assume I’s were remapped so that larger I’s get smaller indices.
        // Hence query(r) is actually max over original I>something.
        return query(r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; 
    cin >> N;
    vector<int> B(N), I(N), R(N);
    for(int i = 0; i < N; i++) cin >> B[i];
    for(int i = 0; i < N; i++) cin >> I[i];
    for(int i = 0; i < N; i++) cin >> R[i];

    // Compress I in descending order so that higher original I get smaller comp‐index:
    vector<int> coords = I;
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    auto getCI = [&](int x){
        // original: small I → small index. We want reversed:
        int pos = int(lower_bound(coords.begin(), coords.end(), x) - coords.begin()) + 1;
        return int(coords.size()) - pos + 1;
    };
    int M = coords.size();

    // Prepare sorting by B desc:
    vector<int> pts(N);
    iota(pts.begin(), pts.end(), 0);
    sort(pts.begin(), pts.end(), [&](int a, int b){
        return B[a] > B[b];
    });

    Fenwick ft(M);
    long long dominated = 0;

    // process blocks of equal B
    for(int i = 0, j; i < N; i = j) {
        for(j = i; j < N && B[pts[j]] == B[pts[i]]; ++j);
        // [i..j) all have same B, none can dominate each other on B
        // so first query them
        for(int k = i; k < j; ++k) {
            int p = pts[k];
            int ci = getCI(I[p]);
            // max R among prior points with I > I[p] is ft.query(ci-1)
            // since reversed mapping: bigger I → smaller ci
            int maxR = ft.query(ci - 1);
            if(maxR > R[p]) 
                dominated++;
        }
        // then add them
        for(int k = i; k < j; ++k) {
            int p = pts[k];
            int ci = getCI(I[p]);
            ft.update(ci, R[p]);
        }
    }

    cout << dominated << "\n";
    return 0;
}
