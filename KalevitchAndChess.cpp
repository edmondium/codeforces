#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> g(8);
    for (auto &row : g) cin >> row;

    array<bool,8> okRow, okCol;
    ranges::for_each(views::iota(0,8), [&](int i){
        okRow[i] = ranges::all_of(g[i], [](char c){ return c=='B'; });
    });
    ranges::for_each(views::iota(0,8), [&](int j){
        okCol[j] = ranges::all_of(views::iota(0,8), [&](int i){ return g[i][j]=='B'; });
    });

    atomic<int> answer(16);

    #pragma omp parallel for
    for (int mask=0; mask<(1<<8); mask++) {
        int strokes = __builtin_popcount(mask);
        bool bad = false;

        for (int i=0; i<8; i++)
            if ((mask & (1<<i)) && !okRow[i]) { bad=true; break; }
        if (bad) continue;

        array<bool,8> needCol{};
        for (int i=0; i<8; i++) if (!(mask & (1<<i)))
            for (int j=0; j<8; j++) if (g[i][j]=='B') needCol[j]=true;

        for (int j=0; j<8; j++) {
            if (needCol[j] && !okCol[j]) { bad=true; break; }
            if (needCol[j]) strokes++;
        }
        if (bad) continue;

        answer.store(min(answer.load(), strokes));
    }

    cout << answer.load() << '\n';
}
