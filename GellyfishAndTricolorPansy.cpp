#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while(t--) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        
        // The effective "budget" on each side is the minimum of (hero HP, knight HP).
        long long gellyfishBudget = min(a, c);
        long long flowerBudget = min(b, d);
        
        // In case of a tie the first mover advantage gives the win to Gellyfish.
        if(gellyfishBudget >= flowerBudget)
            cout << "Gellyfish\n";
        else
            cout << "Flower\n";
    }
    
    return 0;
}
