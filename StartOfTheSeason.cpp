#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int* M = new int[n * n];

    #pragma acc parallel loop collapse(2) copyout(M[0:n*n])
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1; ++j)
            M[i * n + j] = 1 + (i + j) % (n - 1);

    #pragma acc parallel loop copy(M[0:n*n])
    for (int i = 0; i < n - 1; ++i) {
        M[i * n + (n - 1)] = M[i * n + i];
        M[(n - 1) * n + i] = M[i * n + i];
    }

    #pragma acc parallel loop copy(M[0:n*n])
    for (int i = 0; i < n; ++i)
        M[i * n + i] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << M[i * n + j] << ' ';
        cout << '\n';
    }

    delete[] M;
}
