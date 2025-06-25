#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A;
    cin >> A;

    ll totalSum = 0;
    for(int b = 2; b <= A - 1; ++b){
        int x = A;
        while(x){
            totalSum += x % b;
            x /= b;
        }
    }

    ll cnt = A - 2;
    ll g = gcd(totalSum, cnt);
    cout << (totalSum / g) << "/" << (cnt / g) << "\n";
    return 0;
}
