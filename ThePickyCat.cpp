#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a)
            cin >> x;
        
        // For a single element, a1 is automatically the median.
        if(n == 1){
            cout << "YES" << "\n";
            continue;
        }
        
        int b1 = abs(a[0]);
        int X = 0, Y = 0;
        for (int i = 1; i < n; i++){
            int b = abs(a[i]);
            if(b < b1)
                X++;
            else if(b > b1)
                Y++;
        }
        
        // The median is defined as the ceil(n/2)-th smallest element.
        int k = (n + 1) / 2; // k-1 elements must be positioned below the median.
        
        // Two candidate conditions:
        // 1. Candidate positive (a1 remains positive): condition X <= k-1.
        // 2. Candidate negative (flip a1 so it becomes negative): condition k-1 <= Y.
        bool candidatePositive = (X <= (k - 1));
        bool candidateNegative = ((k - 1) <= Y);
        
        cout << ((candidatePositive || candidateNegative) ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
