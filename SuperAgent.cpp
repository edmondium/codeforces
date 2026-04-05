#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> a(3);
    ranges::for_each(a, [](auto& row){ cin >> row; });

    bool symmetric = true;
    #pragma acc parallel loop collapse(2) reduction(&:symmetric)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            symmetric &= (a[i][j] == a[2 - i][2 - j]);

    cout << (symmetric ? "YES\n" : "NO\n");
}
