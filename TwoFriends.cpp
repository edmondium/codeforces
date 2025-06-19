#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <ctime>
#include <complex>
using namespace std;

const double eps = 1e-10;

const int DIM = 2;

typedef complex<double> point;
typedef pair<point, double> circle;
double T1, T2;
point cinema, shop, home;

inline double dist(const point& a, const point& b) {
    return abs(a - b);
}

void readPoint(point& p) {
    double x, y;
    cin >> x >> y;
    p = point(x, y);
}

inline bool isIn(const circle& a, const circle& b) {
    double A = dist(a.first, b.first) + a.second;
    double B = b.second;
    return A < B + eps;
}

inline bool isInPoint(const point& p, const circle& c) {
    return dist(p, c.first) < c.second + eps;
}

inline bool doesIntersect(const circle& a, const circle& b) {
    return dist(a.first, b.first) < a.second + b.second + eps;
}

point getNewCoords(point e1prime, point e2prime, point P, point A) {
    double c1 = A.real() - P.real();
    double c2 = A.imag() - P.imag();
    double x = c1 * e1prime.real() + c2 * e2prime.real();
    double y = c1 * e1prime.imag() + c2 * e2prime.imag();
    return point(x, y);
}

point getOldCoors(point e1prime, point e2prime, point P, point A) {
    double a1 = A.real();
    double a2 = A.imag();
    double x = a1 * e1prime.real() + a2 * e1prime.imag();
    double y = a1 * e2prime.real() + a2 * e2prime.imag();
    x += P.real();
    y += P.imag();
    return point(x, y);
}

vector<point> getIntersectedPoints(const circle& C1, const circle& C2) {
    point P = C1.first;
    point e1prime = C2.first - C1.first;
    e1prime = e1prime / abs(e1prime);
    point e2prime = point(e1prime.imag(), -e1prime.real());
    point A = getNewCoords(e1prime, e2prime, P, C1.first);
    point B = getNewCoords(e1prime, e2prime, P, C2.first);
    double R1 = C1.second * C1.second;
    double R2 = C2.second * C2.second;
    double b = B.real();
    double x = (b * b + R1 - R2) / (2.0 * b);
    double Y = R1 - x * x;
    if (Y < 0.0) Y = 0.0;
    vector<point> ret;
    if (Y < eps) {
        ret.push_back(point(x, Y));
    }
    else {
        ret.push_back(point(x, sqrt(Y)));
        ret.push_back(point(x, -sqrt(Y)));
    }
    for (int i = 0; i < int(ret.size()); ++i) {
        ret[i] = getOldCoors(e1prime, e2prime, P, ret[i]);
    }
    return ret;
}

bool my_comp(const circle& c1, const circle& c2) {
    if (c1.first.real() < c2.first.real()) return true;
    if (c1.first.real() > c2.first.real()) return false;
    if (c1.first.imag() < c2.first.imag()) return true;
    if (c1.first.imag() > c2.first.imag()) return false;
    if (c1.second < c2.second) return true;
    return false;
}

bool intersect3Circles(vector<circle>& circles) {
    sort(circles.begin(), circles.end(), my_comp);
    do {
        if (!doesIntersect(circles[0], circles[1])) {
            return false;
        }
        if (isIn(circles[0], circles[1])) {
            if (doesIntersect(circles[0], circles[2])) {
                return true;
            }
            else {
                return false;
            }
        }
    } while (next_permutation(circles.begin(), circles.end(), my_comp));

    sort(circles.begin(), circles.end(), my_comp);
    do {
        vector<point> pts = getIntersectedPoints(circles[0], circles[1]);
        bool ok = false;
        for (int i = 0; i < int(pts.size()); ++i) {
            if (isInPoint(pts[i], circles[2])) {
                ok = true;
                break;
            }
        }
        if (ok) return true;
    } while(next_permutation(circles.begin(), circles.end(), my_comp));
    return false;
}

bool check(double Q) {
    vector<circle> circles(3);
    circles[0] = circle(cinema, Q);
    circles[1] = circle(shop, max(0.0, T1 - dist(shop, home) - Q));
    circles[2] = circle(home, max(0.0, T2 - Q));
    return intersect3Circles(circles);
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(9);
    double t1, t2;
    cin >> t1 >> t2;
    readPoint(cinema);
    readPoint(home);
    readPoint(shop);
    T2 = t2 + dist(cinema, home);
    T1 = t1 + dist(cinema, shop) + dist(shop, home);
    if (dist(cinema, shop) + dist(shop, home) < T2 + eps) {
        cout << min(T1, T2) << endl;
        return 0;
    }
    double L = 0.0;
    double R = min(T1, T2);
    check(1.000253);
    for (int step = 1; step <= 40; ++step) {
        double Q = (L + R) / 2.0;
        if (check(Q)) {
            L = Q;
        }
        else {
            R = Q;
        }
    }
    cout << (L + R) / 2.0 << endl;
    return 0;
}