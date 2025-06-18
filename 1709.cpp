#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        vector<int>a(n), b(n);
        for(int&i:a) cin>>i;
        for(int&i:b) cin>>i;

        vector<pii> ops;

        // 1) Ensure a[i] < b[i] by vertical swaps
        for(int i=0;i<n;i++){
            if(a[i] > b[i]){
                ops.emplace_back(3, i+1);
                swap(a[i], b[i]);
            }
        }

        // 2) Bubble‐sort a[] with type‐1 swaps
        bool done = false;
        while(!done){
            done = true;
            for(int i=0;i+1<n;i++){
                if(a[i] > a[i+1]){
                    ops.emplace_back(1, i+1);
                    swap(a[i], a[i+1]);
                    done = false;
                }
            }
        }

        // 3) Bubble‐sort b[] with type‐2 swaps
        done = false;
        while(!done){
            done = true;
            for(int i=0;i+1<n;i++){
                if(b[i] > b[i+1]){
                    ops.emplace_back(2, i+1);
                    swap(b[i], b[i+1]);
                    done = false;
                }
            }
        }

        // Output
        cout << ops.size() << "\n";
        for(auto [t,i]: ops)
            cout << t << " " << i << "\n";
    }
    return 0;
}
