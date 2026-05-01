#include <iostream>
#include <cstdio>
#include <cmath>

int main() {
    int l, d, v, g, r;
    if (!(std::cin >> l >> d >> v >> g >> r)) return 0;

    double result = 0.0;

    #pragma acc parallel loop copyout(result)
    for (int i = 0; i < 1; ++i) {
        const double t_to_light = static_cast<double>(d) / v;
        const double cycle = static_cast<double>(g) + r;
        const double t_mod = fmod(t_to_light, cycle);
        
        const double wait = (t_mod >= static_cast<double>(g)) ? (cycle - t_mod) : 0.0;
        
        result = (static_cast<double>(l) / v) + wait;
    }

    std::printf("%.8f\n", result);

    return 0;
}