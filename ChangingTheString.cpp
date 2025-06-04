#include <iostream>
#include <string>
#include <set>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
 
        // We use multisets (ordered by op index) for the beneficial operations.
        multiset<int> opsBA, opsBC, opsCA, opsCB;
        // Operations are given in order 1..q.
        for (int i = 1; i <= q; i++){
            char x, y;
            cin >> x >> y;
            if(x=='b' && y=='a'){
                opsBA.insert(i);
            } else if(x=='b' && y=='c'){
                opsBC.insert(i);
            } else if(x=='c' && y=='a'){
                opsCA.insert(i);
            } else if(x=='c' && y=='b'){
                opsCB.insert(i);
            }
            // Other operations (like a->b, a->c, etc.) would not help in
            // lowering lexicographically so we ignore them.
        }
 
        // We build the answer letter by letter.
        string ans = s;
        for (int i = 0; i < n; i++){
            char c = s[i];
            if(c == 'a'){
                // Already smallest.
                ans[i] = 'a';
            }
            else if(c == 'b'){
                // For letter 'b' the best final letter is 'a'.
                bool converted = false;
                // Option 1: direct (b,a) op if available.
                if(!opsBA.empty()){
                    // Use the op with smallest index.
                    opsBA.erase(opsBA.begin());
                    ans[i] = 'a';
                    converted = true;
                }
                // Option 2: try to get a chain: (b, c) then (c, a).
                else if(!opsBC.empty() && !opsCA.empty()){
                    // Take earliest (b,c) op.
                    auto itBC = opsBC.begin();
                    int indexBC = *itBC;
                    // Find in opsCA an op whose index is greater than indexBC.
                    auto itCA = opsCA.lower_bound(indexBC + 1);
                    if(itCA != opsCA.end()){
                        // Found a valid chain.
                        opsBC.erase(itBC);
                        opsCA.erase(itCA);
                        ans[i] = 'a';
                        converted = true;
                    }
                }
                // If no conversion is possible, the letter stays 'b'.
                if(!converted){
                    ans[i] = 'b';
                }
            }
            else { // c == 'c'
                // For letter 'c', our goal is first to get 'a' (best) if possible.
                bool converted = false;
                // Option 1: direct (c,a).
                if(!opsCA.empty()){
                    opsCA.erase(opsCA.begin());
                    ans[i] = 'a';
                    converted = true;
                }
                // Option 2: try chain: (c,b) then (b,a).
                else if(!opsCB.empty() && !opsBA.empty()){
                    // We need to choose a (c,b) op candidate such that
                    // there is a (b,a) op with a greater index.
                    bool chainDone = false;
                    for(auto itCB = opsCB.begin(); itCB != opsCB.end(); ++itCB){
                        int indexCB = *itCB;
                        auto itBA = opsBA.lower_bound(indexCB + 1);
                        if(itBA != opsBA.end()){
                            // Use these two ops.
                            opsCB.erase(itCB);
                            opsBA.erase(itBA);
                            ans[i] = 'a';
                            chainDone = true;
                            converted = true;
                            break;
                        }
                    }
                    if(!chainDone){
                        // Option 3 below might still apply.
                    }
                }
                // Option 3: if we cannot reach 'a', try to drop c to b with a (c,b) op.
                if(!converted){
                    if(!opsCB.empty()){
                        opsCB.erase(opsCB.begin());
                        ans[i] = 'b';
                        converted = true;
                    }
                    else {
                        ans[i] = 'c';
                    }
                }
            }
        }
 
        cout << ans << "\n";
    }
    return 0;
}
