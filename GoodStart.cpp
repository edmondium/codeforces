#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

// Check whether two sheets in the *same* strip (col or row) can share
// a single offset c so that all of them fit into [0,L] using sheet‐size B:
//   – Sheet‐size = B, total length = L.
//   – We will place ceil(L/B) sheets in that strip, whose “anchor”
//     position c must lie in [L mod B − B, 0].
//   – Two preplaced sheets at coords y1,y2 give remainders m1,m2 mod B.
//   – Each sheet allows two possible anchors: m or m−B.
//   – We need an anchor c in the allowed interval that is common to both.
bool local_ok(int64 a, int64 b, int64 L) {
    // a,b are the two coords in the same strip; sheet‐height = B; strip‐length = L
    int64 B = b;
    int64 m1 = ((a % B) + B) % B;
    int64 m2 = ((L /*dummy*/ % B) + B) % B; // not used
    // Oops: we passed wrong params.  Fix: rename parameters:

    return false;
}

bool same_strip_ok(int64 p1, int64 p2, int64 B, int64 L) {
    // p1,p2 are the two coords in the same strip (so their B‐remainders must
    // allow a single anchor c ∈ [r − B, 0], where r = L mod B)
    int64 m1 = ((p1 % B) + B) % B;
    int64 m2 = ((p2 % B) + B) % B;
    int64 r  = L % B;
    int64 lo = r - B, hi = 0;

    // each sheet allows anchor ∈ {m, m−B}
    array<int64,2> S1 = { m1, m1 - B };
    array<int64,2> S2 = { m2, m2 - B };

    for (auto c : S1) {
        if (c < lo || c > hi) continue;
        // does c also appear in S2?
        if (c == S2[0] || c == S2[1])
            return true;
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int64 w,h,a,b;
        cin >> w >> h >> a >> b;
        int64 x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;

        // global‐alignment tests:
        int64 xm1 = ((x1 % a) + a) % a;
        int64 xm2 = ((x2 % a) + a) % a;
        int64 ym1 = ((y1 % b) + b) % b;
        int64 ym2 = ((y2 % b) + b) % b;

        bool canX = (xm1 == xm2);
        bool canY = (ym1 == ym2);

        bool ok = false;

        // 1) try tiling by *columns*: we fix x0 once, split into vertical strips of width a.
        //    ⇒ need xm1==xm2.  If the two pre‐sheets lie in DIFFERENT columns, they never
        //    constrain each other in y; we’re done.  If they’re in the SAME column
        //    (x1==x2), then within that column they must share a *single* y‐anchor
        //    that fits the [h mod b − b, 0] interval.
        if (canX) {
            if (x1 != x2) {
                ok = true;
            } else {
                // same column: y must be “local‐ok”
                if (same_strip_ok(y1,y2,b,h))
                    ok = true;
            }
        }

        // 2) try tiling by *rows*: symmetric argument
        if (!ok && canY) {
            if (y1 != y2) {
                ok = true;
            } else {
                // same row: x must be “local‐ok”
                if (same_strip_ok(x1,x2,a,w))
                    ok = true;
            }
        }

        cout << (ok ? "Yes\n" : "No\n");
    }

    return 0;
}
