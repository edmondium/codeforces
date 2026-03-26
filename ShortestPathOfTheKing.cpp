#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

struct Pos { int x, y; };

auto parse = [](string s) {
    return Pos{ s[0] - 'a' + 1, s[1] - '0' };
};

auto step = [](Pos &p, const Pos &t) {
    string move;
    if (t.x > p.x) { move += 'R'; p.x++; }
    else if (t.x < p.x) { move += 'L'; p.x--; }
    if (t.y > p.y) { move += 'U'; p.y++; }
    else if (t.y < p.y) { move += 'D'; p.y--; }
    return move;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s >> t;
    Pos start = parse(s), target = parse(t);

    int moves = max(abs(target.x - start.x), abs(target.y - start.y));
    cout << moves << "\n";

    vector<string> path;
    path.reserve(moves);

    while (start.x != target.x || start.y != target.y)
        path.push_back(step(start, target));

    #pragma omp parallel for
    for (int i = 0; i < (int)path.size(); i++)
        cout << path[i] << "\n";
}
