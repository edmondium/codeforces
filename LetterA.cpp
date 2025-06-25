#include <iostream>
#include <array>
#include <algorithm>
using namespace std;
using ll = long long;

struct Point {
    ll x, y;
    Point() : x(0), y(0) {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}

    void init() {
        cin >> x >> y;
    }

    bool operator!=(const Point &o) const {
        return x != o.x || y != o.y;
    }

    Point operator+(const Point &o) const {
        return Point(x + o.x, y + o.y);
    }

    Point operator-(const Point &o) const {
        return Point(x - o.x, y - o.y);
    }

    // cross product
    ll operator*(const Point &o) const {
        return x * o.y - y * o.x;
    }

    // dot product
    ll operator&(const Point &o) const {
        return x * o.x + y * o.y;
    }

    // squared length
    ll len() const {
        return x*x + y*y;
    }
};

struct Line {
    Point a, b;
    void init() {
        a.init();
        b.init();
    }
};

bool check2(const Point &v_cut, const Point &v_leg) {
    // must be collinear, positive dot, and cut-ratio in [1/5,4/5]
    if ( (v_cut * v_leg) == 0        // cross==0: collinear
      && (v_cut & v_leg) > 0        // dot>0: same direction
      && (v_cut.len() * 25 >= v_leg.len())     // (t^2 >= 1/25)
      && (v_cut.len() * 25 <= v_leg.len() * 16) // (t^2 <= 16/25)
    ) {
        return true;
    }
    return false;
}

bool check(const Line &L1, const Line &L2, const Line &L3) {
    // L1.a must coincide with L2.a
    Point O = L1.a;
    if (O != L2.a) return false;

    // angle between L1 and L2 at O must be ≥0°
    Point v1 = L1.b - O;
    Point v2 = L2.b - O;
    if ((v1 & v2) < 0) return false;

    // check cross‐bar L3.a→L3.b cuts both legs in [1/5,4/5]
    if ( check2(L3.a - O, v1) && check2(L3.b - O, v2) ) return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        array<Line,3> seg;
        for (int i = 0; i < 3; i++) {
            seg[i].init();
        }

        bool ok = false;
        // try all flips of endpoints to orient each segment
        for (int f0 = 0; f0 < 2 && !ok; f0++) {
            for (int f1 = 0; f1 < 2 && !ok; f1++) {
                for (int f2 = 0; f2 < 2 && !ok; f2++) {
                    // try each segment as the “common‐leg pair”
                    for (int r = 0; r < 3 && !ok; r++) {
                        int s = (r+1)%3, t = (r+2)%3;
                        if ( check(seg[r], seg[s], seg[t]) ) {
                            ok = true;
                            break;
                        }
                    }
                    swap(seg[0].a, seg[0].b);
                }
                swap(seg[1].a, seg[1].b);
            }
            swap(seg[2].a, seg[2].b);
        }

        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
