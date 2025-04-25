#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; 
    cin >> t;
    
    while(t--) {
        int n, x;
        cin >> n >> x;
        vector<int> perm;
        
        if(x == 0) {
            // Placement of all numbers except 0; then 0 last.
            for (int i = 1; i < n; i++)
                perm.push_back(i);
            perm.push_back(0);
        } else if(x < n) {
            // First, add [0, 1, 2, …, x-1]
            for (int i = 0; i < x; i++)
                perm.push_back(i);
            // Then, add numbers from x+1 to n-1 (all numbers >= x+1)
            for (int i = x + 1; i < n; i++)
                perm.push_back(i);
            // Finally, place x at the end.
            perm.push_back(x);
        } else { // when x == n
            // Use the natural order [0, 1, 2, …, n-1]
            for (int i = 0; i < n; i++)
                perm.push_back(i);
        }
        
        // Output the constructed permutation.
        for (int num : perm)
            cout << num << " ";
        cout << "\n";
    }
    
    return 0;
}
