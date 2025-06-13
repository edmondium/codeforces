#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Event {
    ll cost;
    int idx;
    bool operator<(Event const& o) const {
        return cost > o.cost; // min-heap
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }

        // 1) initial beauty = sum of popcounts
        ll beauty = 0;
        for(ll x : a){
            beauty += __builtin_popcountll(x);
        }

        // 2) for each index, list positions of zero bits (0..61)
        vector<vector<int>> zero_pos(n);
        for(int i = 0; i < n; i++){
            for(int b = 0; b < 62; b++){
                if( ((a[i] >> b) & 1) == 0 )
                    zero_pos[i].push_back(b);
            }
        }

        // 3) pointers into each zero_pos list
        vector<int> ptr(n, 0);
        priority_queue<Event> pq;

        // push first event for each i (if affordable)
        for(int i = 0; i < n; i++){
            if(ptr[i] < (int)zero_pos[i].size()){
                ll delta = 1LL << zero_pos[i][ptr[i]];
                if(delta <= k)
                    pq.push({delta, i});
            }
        }

        // 4) greedily apply cheapest increments
        ll added = 0;
        while(!pq.empty()){
            auto ev = pq.top(); pq.pop();
            if(ev.cost > k) 
                break;

            k -= ev.cost;
            added++;

            int i = ev.idx;
            ptr[i]++;  // consume this zero-bit
            if(ptr[i] < (int)zero_pos[i].size()){
                ll delta = 1LL << zero_pos[i][ptr[i]];
                if(delta <= k)
                    pq.push({delta, i});
            }
        }

        // 5) result
        cout << (beauty + added) << "\n";
    }
    return 0;
}
