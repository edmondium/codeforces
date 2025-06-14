#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// extended Euclid: returns (x,y,d) such that A*x + B*y = d = gcd(A,B)
tuple<ll,ll,ll> ext_gcd(ll A, ll B) {
    if (B==0) return { 1, 0, A };
    auto [x1,y1,d] = ext_gcd(B, A % B);
    ll x = y1;
    ll y = x1 - (A / B) * y1;
    return { x, y, d };
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll A,B,C;
    cin >> A >> B >> C;

    // Solve A*x + B*y = -C
    auto [x0,y0,g] = ext_gcd(llabs(A), llabs(B));
    // adjust signs if A or B negative
    if (A < 0) x0 = -x0;
    if (B < 0) y0 = -y0;

    ll rhs = -C;
    if (rhs % g != 0) {
        cout << "-1\n";
        return 0;
    }

    ll mul = rhs / g;
    ll x = x0 * mul;
    ll y = y0 * mul;

    cout << x << " " << y << "\n";
    return 0;
}
