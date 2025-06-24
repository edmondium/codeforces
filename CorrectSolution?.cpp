#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;

    // Count digits of n
    array<int,10> cnt{};
    for(char c : s) cnt[c - '0']++;

    // Build minimal permutation
    string minimal;
    if(s == "0"){
        minimal = "0";
    } else {
        // pick smallest nonzero to lead
        for(int d = 1; d <= 9; d++){
            if(cnt[d] > 0){
                minimal.push_back(char('0' + d));
                cnt[d]--;
                break;
            }
        }
        // append all remaining digits ascending
        for(int d = 0; d <= 9; d++){
            minimal.append(cnt[d], char('0' + d));
        }
    }

    // Check Bob's answer (as raw string)
    cout << (t == minimal ? "OK\n" : "WRONG_ANSWER\n");
    return 0;
}
