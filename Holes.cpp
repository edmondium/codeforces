#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<int> a(N+2);
    for(int i = 1; i <= N; i++){
        cin >> a[i];
    }

    // block size ~ √N
    int B = int(sqrt(N)) + 1;
    int nb = (N + B - 1) / B;

    vector<int> nxt(N+2), cnt(N+2), last(N+2), blk(N+2);

    // compute block id for each i
    for(int i = 1; i <= N; i++){
        blk[i] = (i-1) / B;
    }

    auto rebuild_block = [&](int id){
        int L = id * B + 1;
        int R = min(N, (id+1)*B);
        for(int i = R; i >= L; i--){
            int j = i + a[i];
            if(j > N || blk[j] != blk[i]){
                nxt[i] = j;
                cnt[i] = 1;
                last[i] = i;
            } else {
                nxt[i] = nxt[j];
                cnt[i] = cnt[j] + 1;
                last[i] = last[j];
            }
        }
    };

    // initial build
    for(int id = nb-1; id >= 0; id--){
        rebuild_block(id);
    }

    while(M--){
        int t, x, y;
        cin >> t >> x;
        if(t == 0){
            // update a[x] = y, then rebuild its block
            cin >> y;
            a[x] = y;
            rebuild_block(blk[x]);
        }
        else {
            // query: throw ball into hole x
            ll total_jumps = 0;
            int pos = x;
            int ans_last = x;
            while(pos <= N){
                total_jumps += cnt[pos];
                ans_last = last[pos];
                pos = nxt[pos];
            }
            cout << ans_last << " " << total_jumps << "\n";
        }
    }

    return 0;
}
