#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w;
    cin >> w;

    auto decision = [&] {
        int result = 0;
        #pragma omp parallel for reduction(|:result)
        for (int i = 0; i < 1; ++i)
            result |= (w % 2 == 0 && w > 2);
        return result ? "YES" : "NO";
    };

    cout << decision();
}
