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
 
        multiset<int> opsBA, opsBC, opsCA, opsCB;
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
            // Other operations are ignored.
        }
 
        string ans = s;
        for (int i = 0; i < n; i++){
            char c = s[i];
            if(c == 'a'){
                ans[i] = 'a';
            }
            else if(c == 'b'){
                bool converted = false;
                // Option 1: Direct b -> a.
                if(!opsBA.empty()){
                    opsBA.erase(opsBA.begin());
                    ans[i] = 'a';
                    converted = true;
                }
                // Option 2: Chain: b -> c then c -> a.
                else if(!opsBC.empty() && !opsCA.empty()){
                    int candidateBC = *opsBC.begin();
                    auto itCA = opsCA.lower_bound(candidateBC + 1);
                    if(itCA != opsCA.end()){
                        opsBC.erase(opsBC.begin());
                        opsCA.erase(itCA);
                        ans[i] = 'a';
                        converted = true;
                    }
                }
                if(!converted){
                    ans[i] = 'b';
                }
            }
            else { // current letter 'c'
                bool converted = false;
                // Option 1: Direct c -> a.
                if(!opsCA.empty()){
                    opsCA.erase(opsCA.begin());
                    ans[i] = 'a';
                    converted = true;
                }
                // Option 2: Chain: c -> b then b -> a.
                else if(!opsCB.empty() && !opsBA.empty()){
                    // Quick check: if even the largest b -> a op is not greater than the smallest c -> b,
                    // then no valid chain exists.
                    if(*opsBA.rbegin() > *opsCB.begin()){
                        int candidateCB = *opsCB.begin();
                        auto itBA = opsBA.lower_bound(candidateCB + 1);
                        // The check *opsBA.rbegin() > candidateCB guarantees that itBA will be valid.
                        if(itBA != opsBA.end()){
                            ans[i] = 'a';
                            opsCB.erase(opsCB.begin());
                            opsBA.erase(itBA);
                            converted = true;
                        }
                    }
                }
                // Option 3: If chain for full conversion to 'a' isn’t possible, try to at least make c -> b.
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
