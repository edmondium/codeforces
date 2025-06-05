#include <iostream>
using namespace std;

int main() {
    int w;
    cin >> w;
    
    // The watermelon can be divided into two even parts if its weight is even and greater than 2.
    if (w > 2 && w % 2 == 0) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    
    return 0;
}
