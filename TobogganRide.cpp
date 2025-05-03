#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long L, t;
    int n;
    cin >> L >> n >> t;
    vector<long long> boosts(n);
    for (auto i {0}; i < n; i++){
        cin >> boosts[i];
    }
    auto canFinish = [&](double c) -> bool{
        double currentVelocity = c;
        double totalTime = 0.0;
        for (auto i {1}; i < n; i++){
            double d = boosts[i] - boosts[i - 1];
            if (currentVelocity * currentVelocity < 2.0 * d)
            return false;
        double segmentTime = currentVelocity - sqrt(currentVelocity * currentVelocity - 2.0 * d);
        totalTime += segmentTime;
        currentVelocity = sqrt(currentVelocity *currentVelocity - 2.0 * d) + c;
        }
        double d = L - boosts[n - 1];
        if (currentVelocity * currentVelocity < 2.0 * d)
        return false;
        double segmentTime = currentVelocity - sqrt(currentVelocity * currentVelocity - 2.0 * d);
        totalTime += segmentTime;
        return totalTime <= t + 1e-9;
    };
    double lo = 0.0;
    double hi = double(L) + 10.0;
    double mid;
    for (auto i {0}; i < 100; i++){
        mid = (lo + hi) / 2.0;
        if (canFinish(mid))
        hi = mid;
    else
    lo = mid;
    }
    cout << fixed << setprecision(6) << hi << endl;
    return 0;
}