#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    // Input guarantees a sorted descending and a[n-1] == 1.
    // If not, uncomment next line:
    // sort(a.begin(), a.end(), greater<ll>());

    auto greedyCount = [&](ll x)->ll {
        ll cnt = 0;
        for(int i = 0; i < n; i++){
            cnt += x / a[i];
            x %= a[i];
            if(x == 0) break;
        }
        return cnt;
    };

    ll best = LLONG_MAX;
    // Try each pair (i,j): we’ll construct sum S = (a[i-1]-1 greedy up to j) + a[j]
    for(int i = 1; i < n; i++){
        // we're interested in breaking at coin value a[i-1]
        for(int j = i; j < n; j++){
            ll need = a[i-1] - 1;
            ll sum = 0;
            ll cnt = 0;
            // greedy on coins a[0..j] to represent (a[i-1]-1)
            for(int k = 0; k <= j && need > 0; k++){
                ll use = need / a[k];
                cnt += use;
                sum += use * a[k];
                need -= use * a[k];
            }
            // now add one more coin of a[j]
            sum += a[j];
            cnt++;

            // compare to true greedy on the full set
            ll g = greedyCount(sum);
            if(cnt < g){
                best = min(best, sum);
            }
        }
    }

    if(best == LLONG_MAX) 
        cout << -1 << "\n";
    else
        cout << best << "\n";

    return 0;
}
