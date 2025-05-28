#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while(t--) {
        int n;
        cin >> n;
        
        int count = 0;
        int last = -1; // will hold the last selected value
        bool first = true;
        
        // Process each element in the sorted array.
        // As soon as we encounter the first number, we choose it.
        // Then for each subsequent number, we choose it only if it is at least last + 2.
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (first) { // always choose the first number
                last = x;
                count++;
                first = false;
            } else if (x >= last + 2) {
                last = x;
                count++;
            }
        }
        
        cout << count << "\n";
    }
    
    return 0;
}
