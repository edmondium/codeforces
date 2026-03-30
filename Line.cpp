#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
using ll = long long;

auto ext_gcd = [](auto self, ll A, ll B) -> tuple<ll,ll,ll> {
    if (B==0) return {1,0,A};
    auto [x1,y1,d] = self(self,B,A%B);
    return tuple<ll,ll,ll>{y1, x1-(A/B)*y1, d};
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll A,B,C;
    cin >> A >> B >> C;
    auto [x0,y0,g] = ext_gcd(ext_gcd,llabs(A),llabs(B));
    if (A<0) x0=-x0;
    if (B<0) y0=-y0;
    ll rhs=-C;
    if (rhs%g!=0) {
        cout << -1 << "\n";
        return 0;
    }
    ll mul=rhs/g;
    ll x,y;
    #pragma omp parallel sections
    {
        #pragma omp section
        { x=x0*mul; }
        #pragma omp section
        { y=y0*mul; }
    }
    cout << x << " " << y << "\n";
}
