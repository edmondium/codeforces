#include <bits/stdc++.h>
#include <numeric>
using namespace std;

using i64 = long long;

auto digit_sum = [](int A, int b) {
    int x = A;
    i64 s = 0;
    while (x) {
        s += x % b;
        x /= b;
    }
    return s;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A;
    cin >> A;

    i64 totalSum = 0;
    #pragma omp parallel for reduction(+:totalSum)
    for (int b = 2; b <= A - 1; ++b) {
        totalSum += digit_sum(A, b);
    }

    i64 cnt = A - 2;
    i64 g = std::gcd(totalSum, cnt);
    cout << (totalSum / g) << "/" << (cnt / g) << "\n";
}
