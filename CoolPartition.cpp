#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; 
    cin >> t;
    while(t--){
        int n; 
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        
        // Precompute the last occurrence for each value (values are 1-indexed up to n)
        vector<int> lastOcc(n + 1, -1);
        for (int i = 0; i < n; i++){
            lastOcc[a[i]] = i;
        }
        
        int segments = 0;
        int pos = 0;
        
        // We'll use bitset to store the "required" set from previous segments.
        // Use 200001 bits (indices 1..n used).
        bitset<200001> req; 
        req.reset(); // initially empty

        // Process segments from left to right.
        while(pos < n){
            bitset<200001> cur;
            cur.reset();
            int curMin = n; // minimum among lastOcc for elements in the current segment
    
            bool cutMade = false;
            int i;
            for(i = pos; i < n; i++){
                int val = a[i];
                // If this number is not already in the current segment, add it.
                if(!cur.test(val)){
                    cur.set(val);
                    curMin = min(curMin, lastOcc[val]); // update current segment's minimum last occurrence.
                }
                // We consider a potential cut if we are not at the last element.
                if(i < n - 1 && i < curMin){
                    // Check if the required set (elements that must appear, carried over from previous segment)
                    // is a subset of our current segment set ("cur").
                    // (req & cur) will equal req if req ⊆ cur.
                    if((req & cur) == req){
                        // We can safely cut the segment here.
                        segments++;
                        req = cur;  // the union of this segment becomes the new requirement.
                        pos = i + 1;
                        cutMade = true;
                        break;
                    }
                }
            }
            // If we did not make any cut (i.e. no valid non-final cut was found), the remainder forms the final segment.
            if(!cutMade){
                segments++; 
                break;
            }
        }
 
        cout << segments << "\n";
    }
    return 0;
}
