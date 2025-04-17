#include <iostream>
#include <array>
#include <cmath>
#include <format>

typedef long long ll;
using Point = std::array<double, 2>;
using Triangle = std::array<Point, 3>;

double calculatorNumber(double a, double b) {
    if (std::abs(b) <= 1e-2)
        return a;
    return calculatorNumber(b, std::fmod(a, b));
}

double calculatorDistance(const Point& p1, const Point& p2) {
    return std::sqrt((p2[0] - p1[0]) * (p2[0] - p1[0]) + (p2[1] - p1[1]) * (p2[1] - p1[1]));
}

int main() {
    Triangle point;
    std::array<double, 3> dis, angle;
    double p, sum = 0, area = 0, r, res;

    res = std::acos(-1.0);

    for (auto& p : point) {
        std::cin >> p[0] >> p[1];
    }

    for (int i = 0; i < 3; i++) {
        dis[i] = calculatorDistance(point[i], point[(i + 1) % 3]);
        sum += dis[i];
    }

    p = sum / 2;
    area = std::sqrt(p * (p - dis[0]) * (p - dis[1]) * (p - dis[2]));
    r = (dis[0] * dis[1] * dis[2]) / (4 * area);

    for (int i = 0; i < 3; i++) {
        double value = 1 - dis[i] * dis[i] / (2 * r * r);
        value = std::clamp(value, -1.0, 1.0);
        angle[i] = std::acos(value);
    }

    angle[2] = 2 * res - angle[0] - angle[1];

    for (int i = 1; i < 3; i++) {
        angle[i] = calculatorNumber(angle[i - 1], angle[i]);
    }

    std::cout << std::format("{:.6f}\n", r * r * std::sin(angle[2]) * res / angle[2]);

    return 0;
}
