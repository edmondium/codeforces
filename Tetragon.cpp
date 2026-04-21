#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <ranges>
#include <optional>
#include <openacc.h>

using namespace std;

using ld = long double;
const ld eps = 1e-10;

struct Vec {
    ld x, y;
    
    constexpr Vec operator+(const Vec& o) const { return {x + o.x, y + o.y}; }
    constexpr Vec operator-(const Vec& o) const { return {x - o.x, y - o.y}; }
    constexpr Vec operator*(ld k) const { return {x * k, y * k}; }
    
    constexpr void rotate() {
        ld tmp = x;
        x = -y;
        y = tmp;
    }
};

struct Line {
    ld a, b, c;
    Line(const Vec& p1, const Vec& p2) : a(p1.y - p2.y), b(p2.x - p1.x), c(p1.x * p2.y - p1.y * p2.x) {}
};

auto crossp = [](const Vec& v1, const Vec& v2) constexpr {
    return v1.x * v2.y - v1.y * v2.x;
};

auto intersect = [](const Line& l1, const Line& l2) constexpr -> Vec {
    ld k = l1.a * l2.b - l1.b * l2.a;
    return Vec{(l1.b * l2.c - l1.c * l2.b) / k, (l1.c * l2.a - l1.a * l2.c) / k};
};

auto validate = [](const array<Vec, 4>& a) -> bool {
    auto side_cross = [&](int i) {
        return crossp(a[(i + 1) % 4] - a[i], a[(i + 2) % 4] - a[(i + 1) % 4]);
    };

    ld first = side_cross(0);
    if (abs(first) < eps) return false;
    bool positive = first > 0;

    return ranges::all_of(views::iota(1, 4), [&](int i) {
        ld cp = side_cross(i);
        return abs(cp) > eps && (cp > 0) == positive;
    });
};

void solve() {
    array<Vec, 3> p;
    for (auto& pt : p) cin >> pt.x >> pt.y;

    auto result = views::iota(0, 3) 
        | views::transform([&](int i) -> std::optional<array<Vec, 4>> {
            array<Vec, 3> curr = p;
            if (i == 1) swap(curr[0], curr[1]), swap(curr[1], curr[2]);
            if (i == 2) swap(curr[1], curr[2]), swap(curr[0], curr[1]);

            Vec v21 = curr[0] - curr[1];
            Vec v13 = curr[2] - curr[0];
            Vec pA = curr[0] + v21 * 0.5;
            Vec pB = curr[0] + v13 * 0.5;
            v21.rotate();
            v13.rotate();

            Line l1(pA, pA + v21);
            Line l2(pB, pB + v13);

            if (abs(l1.a * l2.b - l1.b * l2.a) < eps) return nullopt;

            array<Vec, 4> res;
            res[0] = intersect(l1, l2);
            res[1] = curr[0] * 2.0 - res[0];
            res[2] = curr[1] * 2.0 - res[1];
            res[3] = curr[2] * 2.0 - res[0];

            if (validate(res)) return res;
            return nullopt;
        })
        | views::filter([](const auto& opt) { return opt.has_value(); })
        | views::take(1);

    if (!result.empty()) {
        auto final_pts = *result.front();
        cout << "YES\n";
        for (const auto& pt : final_pts) {
            cout << fixed << setprecision(9) << pt.x << " " << pt.y << " ";
        }
        cout << "\n";
    } else {
        cout << "NO\n\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;
    
    #pragma acc data copyin(eps)
    {
        while (t--) {
            solve();
        }
    }
    return 0;
}