#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (auto &x : a) {
            cin >> x;
        }
        
        // For an arithmetic progression, the common difference d must satisfy:
        long long d = a[1] - a[0];
        bool isArithmetic = true;
        for (int i = 0; i < n; i++) {
            // Check if a[i] equals a[0] + i*d.
            if (a[i] != a[0] + (long long)i * d) {
                isArithmetic = false;
                break;
            }
        }
        
        if (!isArithmetic) {
            cout << "NO\n";
            continue;
        }
        
        // We rewrite the operation on the first element:
        // a1 = x + n*y with also x-y = d, so x = y + d.
        // Hence a1 = (y+d) + n*y = d + (n+1)*y.
        // => y = (a1 - d) / (n + 1) should be an integer and nonnegative.
        if ((a[0] - d) % (n + 1) != 0) {
            cout << "NO\n";
            continue;
        }
        
        long long y = (a[0] - d) / (n + 1);
        long long x = y + d;
        if (x < 0 || y < 0) {
            cout << "NO\n";
            continue;
        }
        
        cout << "YES\n";
    }
    
    return 0;
}
