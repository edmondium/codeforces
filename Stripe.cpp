#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    long long* arr = new long long[n];
    for (int i = 0; i < n; ++i) cin >> arr[i];

    long long total = accumulate(arr, arr + n, 0LL);
    if (total % 2 != 0) {
        cout << 0 << '\n';
        delete[] arr;
        return 0;
    }

    long long half = total / 2;
    long long ways = 0;
    long long prefix = 0;

    #pragma acc parallel loop reduction(+:ways) copyin(arr[0:n]) private(prefix)
    for (int i = 0; i < n - 1; ++i) {
        prefix += arr[i];
        if (prefix == half) ways++;
    }

    cout << ways << '\n';
    delete[] arr;
}
