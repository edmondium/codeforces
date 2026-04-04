#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long x;
    cin >> x;
    long long t = llabs(x);

    long long k = 0, S = 0;
    while (S < t || ((S - t) & 1)) {
        ++k;
        #pragma omp parallel reduction(+:S)
        {
            #pragma omp single
            S += k;
        }
    }

    cout << k << '\n';
}
