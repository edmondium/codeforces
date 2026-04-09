#include <bits/stdc++.h>
#include <openacc.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, x, y;
    cin >> a >> b >> x >> y;

    auto g = gcd(x, y);
    x /= g; y /= g;

    long long k;
    #pragma acc parallel loop reduction(min:k)
    for (int i = 0; i < 1; ++i)
        k = min(a / x, b / y);

    cout << (k ? format("{} {}", k * x, k * y) : "0 0") << '\n';
}