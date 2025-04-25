#include <iostream>
#include <string>
using namespace std;

void solve_test_case() {
    int n;
    string s;
    cin >> n >> s;
    
    int total_ones = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            // n-1 strings will keep 1, one string will have 0
            total_ones += n - 1;
        } else {
            // n-1 strings will keep 0, one string will have 1
            total_ones += 1;
        }
    }
    cout << total_ones << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--) {
        solve_test_case();
    }
    return 0;
}