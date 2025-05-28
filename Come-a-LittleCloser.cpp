#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<pair<ll,ll>> pts(n);
        for (int i = 0; i < n; i++){
            cin >> pts[i].first >> pts[i].second;
        }
        
        // If there is only one monster then the rectangle is 1x1.
        if(n == 1){
            cout << 1 << "\n";
            continue;
        }
        
        // Compute the global min and max for x and y
        // Also record the "second" min and max and the frequency of the extreme values.
        ll minX = LLONG_MAX, maxX = 0;
        ll secondMinX = LLONG_MAX, secondMaxX = 0;
        ll minY = LLONG_MAX, maxY = 0;
        ll secondMinY = LLONG_MAX, secondMaxY = 0;
        ll cntMinX = 0, cntMaxX = 0, cntMinY = 0, cntMaxY = 0;
        
        for(auto &p : pts){
            ll x = p.first, y = p.second;
            // For x:
            if(x < minX) {
                secondMinX = minX;
                minX = x;
                cntMinX = 1;
            } else if(x == minX) {
                cntMinX++;
            } else if(x < secondMinX){
                secondMinX = x;
            }
            
            if(x > maxX){
                secondMaxX = maxX;
                maxX = x;
                cntMaxX = 1;
            } else if(x == maxX){
                cntMaxX++;
            } else if(x > secondMaxX){
                secondMaxX = x;
            }
            
            // For y:
            if(y < minY) {
                secondMinY = minY;
                minY = y;
                cntMinY = 1;
            } else if(y == minY) {
                cntMinY++;
            } else if(y < secondMinY){
                secondMinY = y;
            }
            
            if(y > maxY){
                secondMaxY = maxY;
                maxY = y;
                cntMaxY = 1;
            } else if(y == maxY){
                cntMaxY++;
            } else if(y > secondMaxY){
                secondMaxY = y;
            }
        }
        
        // If all monsters have the same x (or y) then adjust the second-extreme accordingly.
        if(secondMinX == LLONG_MAX)
            secondMinX = minX;
        if(secondMaxX == 0)
            secondMaxX = maxX;
        if(secondMinY == LLONG_MAX)
            secondMinY = minY;
        if(secondMaxY == 0)
            secondMaxY = maxY;
        
        // The rectangle covering all monsters without any move:
        ll origWidth = maxX - minX + 1;
        ll origHeight = maxY - minY + 1;
        ll origArea = origWidth * origHeight;
        
        ll best = origArea;
        
        // Check every candidate monster that we might choose to move.
        for(auto &p : pts){
            ll x = p.first, y = p.second;
            ll L = (x == minX && cntMinX == 1) ? secondMinX : minX;
            ll R = (x == maxX && cntMaxX == 1) ? secondMaxX : maxX;
            ll B = (y == minY && cntMinY == 1) ? secondMinY : minY;
            ll T = (y == maxY && cntMaxY == 1) ? secondMaxY : maxY;
            
            ll width = R - L + 1;
            ll height = T - B + 1;
            ll inside = width * height;  // area of the remaining monsters’ bounding box
            
            ll candidateArea;
            // The remaining (n-1) monsters occupy distinct cells.
            // If some cell inside [L, R]×[B, T] is free then we can reinsert the moved monster inside.
            if(inside > (n - 1))
                candidateArea = inside;
            else
                // Otherwise, the best we can do is extend one side by 1.
                candidateArea = min((width + 1) * height, width * (height + 1));
            
            best = min(best, candidateArea);
        }
        
        cout << best << "\n";
    }
    return 0;
}
