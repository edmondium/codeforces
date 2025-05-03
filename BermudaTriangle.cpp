#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// A simple structure to hold the result of extended gcd computation.
struct Triple {
    ll g, x, y; // g = gcd(a, b) and x, y are the Bézout coefficients: a*x + b*y = g
};

// Standard extended GCD that returns (g, x, y)
Triple extended_gcd(ll a, ll b) {
    if(b == 0) 
        return {a, 1, 0};
    Triple t = extended_gcd(b, a % b);
    return {t.g, t.y, t.x - (a / b) * t.y};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int tc;
    cin >> tc;
    while (tc--) {
        int n, x, y, u, v;
        cin >> n >> x >> y >> u >> v;
        
        // Normalize the velocity vector.
        int d = gcd(u, v);
        u /= d;
        v /= d;
        
        // --- Solve the congruence for the x-coordinate:
        // We want t such that: u * t ≡ -x (mod n)
        // Let g1 = gcd(u, n) must divide x.
        int g1 = gcd(u, n);
        if(x % g1 != 0) {
            cout << -1 << "\n";
            continue;
        }
        int n1 = n / g1;
        int x1 = x / g1;
        int u1 = u / g1;
        // Since gcd(u1, n1) = 1, we can compute the inverse of u1 modulo n1.
        Triple e1 = extended_gcd(u1, n1); // here e1.g must be 1.
        ll inv_u1 = (e1.x % n1 + n1) % n1;
        // A particular solution for t mod n1 is:
        ll a_rem = ((- (ll)x1) % n1 + n1) % n1;
        a_rem = (a_rem * inv_u1) % n1;  // t ≡ a_rem (mod n1)
        
        // --- Solve the congruence for the y-coordinate:
        // We want t such that: v * t ≡ -y (mod n)
        int g2 = gcd(v, n);
        if(y % g2 != 0) {
            cout << -1 << "\n";
            continue;
        }
        int n2 = n / g2;
        int y2 = y / g2;
        int v2 = v / g2;
        Triple e2 = extended_gcd(v2, n2);
        ll inv_v2 = (e2.x % n2 + n2) % n2;
        ll b_rem = ((- (ll)y2) % n2 + n2) % n2;
        b_rem = (b_rem * inv_v2) % n2;  // t ≡ b_rem (mod n2)
        
        // --- Combine the two congruences:
        // We have t ≡ a_rem (mod n1) and t ≡ b_rem (mod n2).
        // Write the combined solution as t = a_rem + n1 * k.
        // We need k such that:
        //      a_rem + n1 * k ≡ b_rem (mod n2)
        // i.e.  n1 * k ≡ (b_rem - a_rem) (mod n2)
        int G = gcd(n1, n2);
        if ((b_rem - a_rem) % G != 0) {
            cout << -1 << "\n";
            continue;
        }
        // Solve n1*k ≡ (b_rem - a_rem) (mod n2)
        // Write it as a linear equation: n1*k + n2*m = (b_rem - a_rem)
        Triple e3 = extended_gcd(n1, n2); // e3.g == G
        // One solution for k is:
        ll k0 = ((b_rem - a_rem) / G) * e3.x;
        // The modulus for k is modK = n2 / G.
        ll modK = n2 / G;
        // Make sure k0 is in the reduced residue system:
        k0 = (k0 % modK + modK) % modK;
        
        // Hence a solution for t is:
        ll T = a_rem + (ll)n1 * k0;
        // The full family of solutions is unique modulo L = lcm(n1, n2) = n1 * (n2 / G).
        ll period = (ll)n1 * modK;
        T %= period;
        T = (T + period) % period;
        if (T == 0)
            T = period;  // We require a positive time.
        
        // --- Update the unfolded coordinates.
        // At time T the plane's position becomes:
        ll X = x + (ll)u * T;
        ll Y = y + (ll)v * T;
        // At escape, both X and Y are multiples of n.
        
        // --- Count the reflections.
        // The count is computed by summing:
        //   - (X/n - 1): the number of vertical boundary hits,
        //   - (Y/n - 1): the number of horizontal boundary hits,
        //   - (X + Y)/(2*n) and |X - Y|/(2*n): contributions from the hypotenuse crossings.
        ll cnt = 0;
        cnt += (X / n - 1);
        cnt += (Y / n - 1);
        cnt += (X + Y) / (2LL * n);
        cnt += abs(X - Y) / (2LL * n);
        cout << cnt << "\n";
    }
    
    return 0;
}
