#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a_i, v_i, l_i, d_i, w_i;
    cin >> a_i >> v_i >> l_i >> d_i >> w_i;
    double A = a_i, V = v_i, L = l_i, D = d_i, W = w_i;

    auto seg1 = [&]() -> pair<double,double> {
        if (V <= W) {
            double d_acc = V*V/(2*A);
            if (D >= d_acc) return {V/A + (D-d_acc)/V, V};
            double s = sqrt(2*A*D);
            return {s/A, s};
        } else {
            double d_accV = V*V/(2*A);
            double d_dec = (V*V-W*W)/(2*A);
            if (D >= d_accV+d_dec) return {V/A + (D-d_accV-d_dec)/V + (V-W)/A, W};
            double contSpeed = sqrt(2*A*D);
            if (contSpeed <= W) return {contSpeed/A, contSpeed};
            double x = sqrt((W*W+2*A*D)/2.0);
            return {(2*x-W)/A, W};
        }
    };

    auto seg2 = [&](double speedAtSign) -> double {
        double L2 = L-D;
        double d_to_V = V>speedAtSign ? (V*V-speedAtSign*speedAtSign)/(2*A) : 0;
        if (L2 > d_to_V) {
            double t_acc = (V-speedAtSign)/A;
            double t_cruise = (L2-d_to_V)/V;
            return t_acc+t_cruise;
        }
        return (-speedAtSign+sqrt(speedAtSign*speedAtSign+2*A*L2))/A;
    };

    double time1=0, speedAtSign=0, time2=0;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            auto [t1, s] = seg1();
            time1 = t1;
            speedAtSign = s;
        }
        #pragma omp section
        {
            #pragma omp critical
            time2 = seg2(speedAtSign);
        }
    }

    cout << fixed << setprecision(12) << time1+time2 << "\n";
}
