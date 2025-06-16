#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int64 k, a, b, x, y;
        cin >> k >> a >> b >> x >> y;

        auto cook = [&](int64 T0, int64 th1, int64 d1, int64 th2, int64 d2) {
            // cook type1 then type2
            int64 c1 = 0, c2 = 0;
            if(T0 >= th1) {
                c1 = (T0 - th1) / d1 + 1;
                T0 -= c1 * d1;
            }
            if(T0 >= th2) {
                c2 = (T0 - th2) / d2 + 1;
            }
            return c1 + c2;
        };

        // A: type1 → type2, B: type2 → type1
        int64 totalA = cook(k, a, x, b, y);
        int64 totalB = cook(k, b, y, a, x);

        cout << max(totalA, totalB) << "\n";
    }
    return 0;
}
