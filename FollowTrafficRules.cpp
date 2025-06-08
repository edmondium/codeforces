#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int a_i, v_i;
    cin >> a_i >> v_i;
    int l_i, d_i, w_i;
    cin >> l_i >> d_i >> w_i;
    double A = a_i, V = v_i;
    double L = l_i, D = d_i, W = w_i;
 
    double time1 = 0.0;
    double speedAtSign = 0.0; // speed when crossing the sign at distance D
 
    // SEGMENT 1: from 0 to D.
    if(V <= W){
        // When the car's maximum speed V is at most the sign limit W,
        // the sign does not force any braking.
        double d_acc = (V * V) / (2 * A);
        if(D >= d_acc) {
            // If there is enough distance to accelerate to V then cruise.
            time1 = V / A + (D - d_acc) / V;
            speedAtSign = V;
        } else {
            // Otherwise, the car cannot reach V.
            speedAtSign = sqrt(2 * A * D);
            time1 = speedAtSign / A;
        }
    } else {
        // When V > W the sign might force braking.
        // There are two cases.
 
        // First, check if you have enough distance to reach V then decelerate from V to W.
        double d_accV = (V * V) / (2 * A);                    // distance to accelerate from 0 to V
        double d_dec = (V * V - W * W) / (2 * A);               // distance to decelerate from V to W
        if(D >= d_accV + d_dec) {
            // You can accelerate fully to V, then (if necessary) cruise, and finally brake.
            time1 = V / A + (D - d_accV - d_dec) / V + (V - W) / A;
            speedAtSign = W;
        } else {
            // Not enough distance to use V.
            // There are two subcases:
            //  a) If accelerating continuously (with no braking) yields a speed ≤ W at D,
            //     then the optimal strategy is to simply accelerate.
            //  b) Otherwise you accelerate to some peak speed x (> W) and then brake to exactly W.
 
            double contSpeed = sqrt(2 * A * D);
            if(contSpeed <= W) {
                time1 = contSpeed / A;
                speedAtSign = contSpeed;
            } else {
                // Compute the peak speed x such that
                //   (distance accelerating from 0 to x) + (distance decelerating from x to W)
                // equals D. (Using maximum deceleration = A.)
                double x = sqrt((W * W + 2 * A * D) / 2.0);
                time1 = (2 * x - W) / A;
                speedAtSign = W;
            }
        }
    }
 
    // SEGMENT 2: from D to L.
    // The car's speed when starting segment 2 is 'speedAtSign'.
    double L2 = L - D;
    double time2 = 0.0;
    // Determine if we can accelerate from speedAtSign to V.
    double d_to_V = 0.0;
    if(V > speedAtSign)
        d_to_V = (V * V - speedAtSign * speedAtSign) / (2 * A);
    if(L2 > d_to_V){
        // You can accelerate to V then cruise.
        double t_acc = (V - speedAtSign) / A;
        double t_cruise = (L2 - d_to_V) / V;
        time2 = t_acc + t_cruise;
    } else {
        // Cannot reach V in the remaining distance; use quadratic formula.
        time2 = (-speedAtSign + sqrt(speedAtSign * speedAtSign + 2 * A * L2)) / A;
    }
 
    double totalTime = time1 + time2;
    cout << fixed << setprecision(12) << totalTime << "\n";
    return 0;
}
