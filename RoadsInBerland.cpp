#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long d[305][305];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> d[i][j];

    int k; cin >> k;
    
    #pragma acc data copy(d)
    {
        while (k--) {
            int a, b; long long c;
            cin >> a >> b >> c;
            --a; --b;

            if (c < d[a][b]) {
                d[a][b] = d[b][a] = c;
            }

            #pragma acc parallel loop collapse(2) present(d)
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    long long via_a_b = d[i][a] + d[a][b] + d[b][j];
                    long long via_b_a = d[i][b] + d[b][a] + d[a][j];
                    if (via_a_b < d[i][j]) d[i][j] = via_a_b;
                    if (via_b_a < d[i][j]) d[i][j] = via_b_a;
                }
            }

            long long sum = 0;
            #pragma acc parallel loop reduction(+:sum) present(d)
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    sum += d[i][j];
                }
            }
            cout << sum << (k == 0 ? "" : " ");
        }
    }
    cout << endl;
    return 0;
}