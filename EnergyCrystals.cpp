#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        unsigned int x;
        cin >> x;
        // The number of bits in x is floor(log2(x)) + 1.
        int bits = 32 - __builtin_clz(x);  // __builtin_clz returns the number of leading zeros in x.
        cout << 2 * bits + 1 << "\n";
    }
    return 0;
}
