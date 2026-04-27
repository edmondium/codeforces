#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <optional>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long double ld;

struct Point { ld x, y; };
struct Result { ld t1, t2; };

bool inPolygon(Point p, const vector<Point>& poly) {
    int n = poly.size();
    const Point* ptr = poly.data();
    bool on_boundary = false;
    int crossings = 0;

    #pragma acc parallel loop copyin(ptr[0:n]) reduction(||:on_boundary) reduction(+:crossings)
    for (int i = 0; i < n; ++i) {
        Point B = ptr[i];
        Point E = ptr[(i + 1) % n];
        ld cross = (p.x - B.x) * (E.y - B.y) - (p.y - B.y) * (E.x - B.x);
        if (abs(cross) < 1e-7) {
            ld dot = (p.x - B.x) * (E.x - B.x) + (p.y - B.y) * (E.y - B.y);
            ld len2 = (E.x - B.x) * (E.x - B.x) + (E.y - B.y) * (E.y - B.y);
            if (dot >= -1e-7 && dot <= len2 + 1e-7) {
                on_boundary = true;
            }
        }
        if (((B.y > p.y) != (E.y > p.y)) &&
            (p.x < (E.x - B.x) * (p.y - B.y) / (E.y - B.y) + B.x)) {
            crossings++;
        }
    }

    if (on_boundary) return true;
    return crossings % 2 != 0;
}

auto get_best(const vector<Result>& candidates) -> optional<Result> {
    auto valid = candidates | views::filter([](const Result& r) {
        return r.t1 >= -1e-9 && r.t2 >= -1e-9;
    });

    if (ranges::empty(valid)) return nullopt;

    return ranges::min(valid, [](const Result& a, const Result& b) {
        if (abs(a.t1 - b.t1) > 1e-9) return a.t1 < b.t1;
        return a.t2 < b.t2;
    });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Point> poly(n);
    for (auto& p : poly) cin >> p.x >> p.y;

    ld xa, ya, xv, yv, zv, Fd, xu, yu, zu;
    cin >> xa >> ya >> xv >> yv >> zv >> Fd >> xu >> yu >> zu;

    ld detVU = xv * yu - yv * xu;
    vector<Result> all_candidates;

    if (abs(detVU) > 1e-9) {
        vector<Result> raw_cands(n * 5, {-2.0, -2.0});
        const Point* p_ptr = poly.data();
        Result* c_ptr = raw_cands.data();

        #pragma acc parallel loop copyin(p_ptr[0:n]) copyout(c_ptr[0:n*5])
        for (int i = 0; i < n; ++i) {
            Point B = p_ptr[i];
            Point nextB = p_ptr[(i + 1) % n];
            Point E = {nextB.x - B.x, nextB.y - B.y};
            
            ld DX0 = B.x - xa, DY0 = B.y - ya;
            ld t10 = (DX0 * yu - DY0 * xu) / detVU;
            ld t1E = (E.x * yu - E.y * xu) / detVU;
            ld t30 = (xv * DY0 - yv * DX0) / detVU;
            ld t3E = (xv * E.y - yv * E.x) / detVU;
            ld t20 = -(zv * t10 + zu * t30) / Fd;
            ld t2E = -(zv * t1E + zu * t3E) / Fd;

            ld s_vals[5] = {0.0, 1.0, -2.0, -2.0, -2.0};
            if (abs(t1E) > 1e-9) s_vals[2] = -t10 / t1E;
            if (abs(t3E) > 1e-9) s_vals[3] = -t30 / t3E;
            if (abs(t2E) > 1e-9) s_vals[4] = -t20 / t2E;

            for (int j = 0; j < 5; ++j) {
                ld s = s_vals[j];
                if (s >= -1e-9 && s <= 1.0 + 1e-9) {
                    ld t1 = t10 + s * t1E;
                    ld t3 = t30 + s * t3E;
                    ld t2 = t20 + s * t2E;
                    if (t1 >= -1e-9 && t2 >= -1e-9 && t3 >= -1e-9) {
                        c_ptr[i * 5 + j] = {max(0.0L, t1), max(0.0L, t2)};
                    }
                }
            }
        }

        auto valid_edge_cands = raw_cands | views::filter([](const Result& r) {
            return r.t1 >= -1e-9 && r.t2 >= -1e-9;
        }) | ranges::to<vector>();

        ranges::copy(valid_edge_cands, back_inserter(all_candidates));

        if (inPolygon({xa, ya}, poly)) {
            all_candidates.push_back({0.0, 0.0});
        }
    } else {
        ld Vx = xv, Vy = yv;
        if (abs(Vx) < 1e-9 && abs(Vy) < 1e-9) { Vx = xu; Vy = yu; }

        auto solve_P_singular = [&](Point P) -> vector<Result> {
            vector<Result> res;
            auto try_add = [&](ld t1, ld t3) {
                if (t1 >= -1e-9 && t3 >= -1e-9) {
                    ld t2 = -(zv * t1 + zu * t3) / Fd;
                    if (t2 >= -1e-9) res.push_back({max(0.0L, t1), max(0.0L, t2)});
                }
            };

            if (abs(xu) > 1e-7) {
                ld t3 = (P.x - xa) / xu;
                if (abs(yu * t3 - (P.y - ya)) < 1e-7) try_add(0, t3);
            } else if (abs(yu) > 1e-7) {
                ld t3 = (P.y - ya) / yu;
                if (abs(xu * t3 - (P.x - xa)) < 1e-7) try_add(0, t3);
            } else if (abs(P.x - xa) < 1e-7 && abs(P.y - ya) < 1e-7) {
                try_add(0, 0);
            }

            if (abs(xv) > 1e-7) {
                ld t1 = (P.x - xa) / xv;
                if (abs(yv * t1 - (P.y - ya)) < 1e-7) try_add(t1, 0);
            } else if (abs(yv) > 1e-7) {
                ld t1 = (P.y - ya) / yv;
                if (abs(xv * t1 - (P.x - xa)) < 1e-7) try_add(t1, 0);
            } else if (abs(P.x - xa) < 1e-7 && abs(P.y - ya) < 1e-7) {
                try_add(0, 0);
            }

            ld detZ = xv * zu - zv * xu;
            if (abs(detZ) > 1e-9) {
                ld t1 = ((P.x - xa) * zu) / detZ;
                ld t3 = (-zv * (P.x - xa)) / detZ;
                if (abs(yv * t1 + yu * t3 - (P.y - ya)) < 1e-7) try_add(t1, t3);
            } else {
                ld detZy = yv * zu - zv * yu;
                if (abs(detZy) > 1e-9) {
                    ld t1 = ((P.y - ya) * zu) / detZy;
                    ld t3 = (-zv * (P.y - ya)) / detZy;
                    if (abs(xv * t1 + xu * t3 - (P.x - xa)) < 1e-7) try_add(t1, t3);
                }
            }
            return res;
        };

        if (abs(Vx) < 1e-9 && abs(Vy) < 1e-9) {
            if (inPolygon({xa, ya}, poly)) {
                auto pts_res = solve_P_singular({xa, ya});
                ranges::copy(pts_res, back_inserter(all_candidates));
            }
        } else {
            vector<Point> boundary_pts(n * 2, {1e18, 1e18});
            const Point* p_ptr = poly.data();
            Point* b_ptr = boundary_pts.data();
            
            #pragma acc parallel loop copyin(p_ptr[0:n]) copyout(b_ptr[0:n*2])
            for (int i = 0; i < n; ++i) {
                Point B = p_ptr[i];
                Point nextB = p_ptr[(i + 1) % n];
                Point E = {nextB.x - B.x, nextB.y - B.y};
                
                b_ptr[i * 2] = B;
                
                ld detEdge = Vx * (-E.y) - Vy * (-E.x);
                if (abs(detEdge) > 1e-9) {
                    ld s = (Vx * (B.y - ya) - Vy * (B.x - xa)) / detEdge;
                    if (s >= -1e-9 && s <= 1.0 + 1e-9) {
                        b_ptr[i * 2 + 1] = {B.x + s * E.x, B.y + s * E.y};
                    }
                }
            }

            auto pt_candidates = boundary_pts 
                | views::filter([](Point p) { return p.x < 1e17 && p.y < 1e17; })
                | views::transform(solve_P_singular) 
                | views::join 
                | ranges::to<vector>();
                
            ranges::copy(pt_candidates, back_inserter(all_candidates));

            if (inPolygon({xa, ya}, poly)) {
                auto pts_res = solve_P_singular({xa, ya});
                ranges::copy(pts_res, back_inserter(all_candidates));
            }
        }
    }

    auto best = get_best(all_candidates);

    if (!best) {
        cout << fixed << setprecision(8) << -1.0 << " " << -1.0 << "\n";
    } else {
        cout << fixed << setprecision(8) << (double)best->t1 << " " << (double)best->t2 << "\n";
    }

    return 0;
}