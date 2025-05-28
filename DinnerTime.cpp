#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m, p, q;
        cin >> n >> m >> p >> q;

        // Observe that the sliding window condition forces the array to be periodic
        // with period p. When n is a multiple of p, the entire array is just 
        // (n/p) copies of a block with sum q, which means the total sum must be (n/p)*q.
        // Otherwise, if n mod p != 0, we have enough freedom in choosing the block
        // (since we can adjust the sum over the incomplete block) so that any m works.
        if (n % p == 0) {
            // exactly full blocks; total sum must be k * q where k = n/p.
            if (m == (n / p) * q)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    
    return 0;
}
