#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int d, sumTime;
    cin >> d >> sumTime;
    vector<int> minTime(d), maxTime(d);
    
    int totalMin = 0, totalMax = 0;
    for (int i = 0; i < d; i++) {
        cin >> minTime[i] >> maxTime[i];
        totalMin += minTime[i];
        totalMax += maxTime[i];
    }
    
    // Check if the sumTime is possible with given bounds
    if(sumTime < totalMin || sumTime > totalMax){
        cout << "NO";
        return 0;
    }
    
    // Construct a solution starting with all minimums
    vector<int> schedule = minTime;
    int extra = sumTime - totalMin;
    
    // Distribute the extra hours across days without surpassing maxTime
    for(int i = 0; i < d && extra > 0; i++){
        int add = min(extra, maxTime[i] - minTime[i]);
        schedule[i] += add;
        extra -= add;
    }
    
    cout << "YES" << "\n";
    for (int i = 0; i < d; i++){
        cout << schedule[i] << (i+1 < d ? " " : "\n");
    }
    
    return 0;
}
