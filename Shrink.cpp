#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        
        // We'll store our permutation in "perm"
        vector<int> perm(n);
        // Set the predetermined endpoints.
        perm[0] = 2;      // first element
        perm[n-1] = 1;    // last element
        
        // The remaining numbers to place are {3, 4, ..., n}.
        int left = 3;     // smallest available from the remaining set
        int right = n;    // largest available from the remaining set
        
        // We'll fill positions 1 to n-2 (i.e. indices 1 through n-2)
        int pos = 1;
        bool takeSmall = true;
        while(pos < n - 1) {
            if(takeSmall) {
                perm[pos] = left;
                left++;
            } else {
                perm[pos] = right;
                right--;
            }
            pos++;
            takeSmall = !takeSmall; // alternate between the smallest and largest available
        }
        
        // Output the permutation.
        for (int x : perm)
            cout << x << " ";
        cout << "\n";
    }
    
    return 0;
}
