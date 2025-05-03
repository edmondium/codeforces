#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        
        int sum = a + b + c;
        // Check if sum is divisible by 3.
        if (sum % 3 != 0) {
            cout << "NO" << endl;
            continue;
        }
        
        int T = sum / 3;
        // T must be at least b to ensure deck2 doesn't get negative additions,
        // and T must be less than c because we have to remove at least one card from deck3.
        if (T < b || T >= c) {
            cout << "NO" << endl;
            continue;
        }
        
        cout << "YES" << endl;
    }
    
    return 0;
}
