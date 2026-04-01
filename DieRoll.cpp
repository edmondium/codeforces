#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int y, w;
    cin >> y >> w;
    int m = max(y, w);
    int num = 6 - m + 1, den = 6;
    int g;
    #pragma omp parallel
    {
        #pragma omp single
        g = gcd(num, den);
    }
    cout << num / g << '/' << den / g << '\n';
}
