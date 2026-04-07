#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Seg { ll x1, y1, x2, y2; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Seg a[4];
    for (int i = 0; i < 4; i++)
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;

    int Hmask[4] = {0}, Vmask[4] = {0};

    #pragma acc parallel loop copyin(a[0:4]) copyout(Hmask[0:4], Vmask[0:4])
    for (int i = 0; i < 4; i++) {
        auto s = a[i];
        if (s.y1 == s.y2 && s.x1 != s.x2) Hmask[i] = 1;
        else if (s.x1 == s.x2 && s.y1 != s.y2) Vmask[i] = 1;
    }

    vector<Seg> H, V;
    for (int i = 0; i < 4; i++) {
        if (Hmask[i]) H.push_back(a[i]);
        if (Vmask[i]) V.push_back(a[i]);
    }

    if (H.size() != 2 || V.size() != 2) {
        cout << "NO\n";
        return 0;
    }

    auto norm = [&](Seg s) {
        if (tie(s.x1,s.y1) > tie(s.x2,s.y2)) swap(s.x1,s.x2), swap(s.y1,s.y2);
        return s;
    };

    transform(H.begin(), H.end(), H.begin(), norm);
    transform(V.begin(), V.end(), V.begin(), norm);

    ll y0 = min(H[0].y1, H[1].y1);
    ll y1 = max(H[0].y1, H[1].y1);
    if (y0 == y1) { cout << "NO\n"; return 0; }

    ll xlo = min({H[0].x1, H[0].x2, H[1].x1, H[1].x2});
    ll xhi = max({H[0].x1, H[0].x2, H[1].x1, H[1].x2});
    if (xlo == xhi) { cout << "NO\n"; return 0; }

    auto covers_h = [&](auto &s) {
        ll lo = min(s.x1, s.x2), hi = max(s.x1, s.x2);
        return (s.y1 == y0 || s.y1 == y1) && lo == xlo && hi == xhi;
    };
    if (!ranges::all_of(H, covers_h)) {
        cout << "NO\n";
        return 0;
    }

    ll x0 = min(V[0].x1, V[1].x1);
    ll x2 = max(V[0].x1, V[1].x1);
    if (x0 != xlo || x2 != xhi) {
        cout << "NO\n";
        return 0;
    }

    ll ybot = min({V[0].y1, V[0].y2, V[1].y1, V[1].y2});
    ll ytop = max({V[0].y1, V[0].y2, V[1].y1, V[1].y2});
    if (ybot != y0 || ytop != y1) {
        cout << "NO\n";
        return 0;
    }

    auto covers_v = [&](auto &s) {
        ll lo = min(s.y1, s.y2), hi = max(s.y1, s.y2);
        return (s.x1 == x0 || s.x1 == x2) && lo == y0 && hi == y1;
    };
    if (!ranges::all_of(V, covers_v)) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
}
