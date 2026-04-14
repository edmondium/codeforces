#include <bits/stdc++.h>
using namespace std;

auto dot = [](auto a, auto b) { return a.first * b.first + a.second * b.second; };
auto sub = [](auto a, auto b) { return pair{a.first - b.first, a.second - b.second}; };

bool isRight(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3) {
    auto area2 = (p2.first - p1.first) * (p3.second - p1.second)
               - (p2.second - p1.second) * (p3.first - p1.first);
    if (area2 == 0) return false;
    auto v1 = sub(p2, p1), v2 = sub(p3, p1);
    auto v3 = sub(p1, p2), v4 = sub(p3, p2);
    auto v5 = sub(p1, p3), v6 = sub(p2, p3);
    return dot(v1, v2) == 0 || dot(v3, v4) == 0 || dot(v5, v6) == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    array<pair<int,int>,3> p;
    for (auto& [x,y] : p) cin >> x >> y;

    if (isRight(p[0],p[1],p[2])) { cout << "RIGHT\n"; return 0; }

    vector<pair<int,int>> shifts = {{1,0},{-1,0},{0,1},{0,-1}};
    bool almost = false;

    #pragma acc parallel loop collapse(2) reduction(||:almost)
    for (int i=0;i<3;i++)
        for (int j=0;j<4;j++) {
            auto q = p;
            q[i].first += shifts[j].first;
            q[i].second += shifts[j].second;
            if (isRight(q[0],q[1],q[2])) almost = true;
        }

    cout << (almost ? "ALMOST\n" : "NEITHER\n");
}
