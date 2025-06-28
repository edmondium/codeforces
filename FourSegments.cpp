#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    struct Seg { ll x1, y1, x2, y2; };
    vector<Seg> H, V;
    for(int i = 0; i < 4; i++) {
        Seg s; 
        cin >> s.x1 >> s.y1 >> s.x2 >> s.y2;
        if (s.y1 == s.y2 && s.x1 != s.x2)
            H.push_back(s);
        else if (s.x1 == s.x2 && s.y1 != s.y2)
            V.push_back(s);
        else {
            cout << "NO\n";
            return 0;
        }
    }
    if (H.size() != 2 || V.size() != 2) {
        cout << "NO\n";
        return 0;
    }

    // Horizontals: extract their Y-levels and X-ranges
    ll y0 = min(H[0].y1, H[1].y1);
    ll y1 = max(H[0].y1, H[1].y1);
    if (y0 == y1) { cout << "NO\n"; return 0; }

    ll xlo = min({H[0].x1, H[0].x2, H[1].x1, H[1].x2});
    ll xhi = max({H[0].x1, H[0].x2, H[1].x1, H[1].x2});
    if (xlo == xhi) { cout << "NO\n"; return 0; }

    auto covers_h = [&](Seg &s) {
        // Does this horizontal sit at one of y0,y1 and span exactly from xlo to xhi?
        ll lo = min(s.x1, s.x2), hi = max(s.x1, s.x2);
        return (s.y1 == y0 || s.y1 == y1) && lo == xlo && hi == xhi;
    };
    if (!covers_h(H[0]) || !covers_h(H[1])) {
        cout << "NO\n";
        return 0;
    }

    // Verticals: extract their X-levels and Y-ranges
    ll x0 = min(V[0].x1, V[1].x1);
    ll x2 = max(V[0].x1, V[1].x1);
    if (x0 != xlo || x2 != xhi) { // must align to horizontal ends
        cout << "NO\n"; 
        return 0;
    }
    ll ybot = min({V[0].y1, V[0].y2, V[1].y1, V[1].y2});
    ll ytop = max({V[0].y1, V[0].y2, V[1].y1, V[1].y2});
    if (ybot != y0 || ytop != y1) {
        cout << "NO\n";
        return 0;
    }

    auto covers_v = [&](Seg &s) {
        // Does this vertical lie on x0 or x2 and span exactly from y0 to y1?
        ll lo = min(s.y1, s.y2), hi = max(s.y1, s.y2);
        return (s.x1 == x0 || s.x1 == x2) && lo == y0 && hi == y1;
    };
    if (!covers_v(V[0]) || !covers_v(V[1])) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    return 0;
}
