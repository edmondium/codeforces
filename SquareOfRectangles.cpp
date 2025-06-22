#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        array<pair<int,int>,3> r;
        for(int i = 0; i < 3; i++){
            cin >> r[i].first >> r[i].second;
        }

        bool ok = false;
        array<int,3> p{0,1,2};
        // try all 6 permutations of which rect is r0, r1, r2
        do {
            auto [l0,b0] = r[p[0]];
            auto [l1,b1] = r[p[1]];
            auto [l2,b2] = r[p[2]];

            // 1) All in one row: same height, widths sum = that height
            if (b0 == b1 && b1 == b2){
                int S = b0;
                if (l0 + l1 + l2 == S){
                    ok = true;
                }
            }

            // 2) All in one column: same width, heights sum = that width
            if (!ok && l0 == l1 && l1 == l2){
                int S = l0;
                if (b0 + b1 + b2 == S){
                    ok = true;
                }
            }

            // 3) Two side-by-side on top, one below:
            //    top row: b0==b1, width W = l0+l1
            //    bottom:   l2==W, and b0 + b2 == W
            if (!ok && b0 == b1){
                int W = l0 + l1;
                if (l2 == W && b0 + b2 == W){
                    ok = true;
                }
            }

            // 4) Two stacked on left, one to the right:
            //    left col: l0==l1, height H = b0+b1
            //    right:    b2==H, and l0 + l2 == H
            if (!ok && l0 == l1){
                int H = b0 + b1;
                if (b2 == H && l0 + l2 == H){
                    ok = true;
                }
            }

            if(ok) break;
        } while(next_permutation(p.begin(), p.end()));

        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}
