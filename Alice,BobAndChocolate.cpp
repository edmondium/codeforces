#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> t(n);
    #pragma omp parallel for
    for (int i = 0; i < n; i++) cin >> t[i];

    int l = 0, r = n - 1;
    long long timeAlice = 0, timeBob = 0;
    int ateAlice = 0, ateBob = 0;

    while (l <= r) {
        if (timeAlice <= timeBob) {
            timeAlice += t[l++];
            ateAlice++;
        } else {
            timeBob += t[r--];
            ateBob++;
        }
    }

    cout << ateAlice << " " << ateBob << "\n";
}
