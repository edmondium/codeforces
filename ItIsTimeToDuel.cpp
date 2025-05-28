#include <iostream>
#include <vector>
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
        for(auto &x : a)
            cin >> x;
        
        // dp[i][val] indicates that we can assign outcomes for duels 0..i 
        // (duel i corresponds to the (i+1)-th duel) such that all conditions for players 1 to i+1 are met
        // with duel i outcome set to 'val'.
        vector<vector<bool>> dp(n-1, vector<bool>(2,false)); // there are n-1 duels
        
        // Base: Duel 0 (the only duel for Player 1) is forced by a[0]:
        // if a[0]==0 -> player 1 must lose the duel so x[0] = 0;
        // if a[0]==1 -> player 1 must win so x[0] = 1.
        if(a[0] == 0)
            dp[0][0] = true;
        else
            dp[0][1] = true;
        
        // Process duels 1 to n-2. 
        // Duel index i (1-indexed if you add 1) will decide the outcome for the (i+1)-th duel,
        // and affect player (i+1) (0-indexed as i in the array 'a').
        for (int duel = 1; duel < n-1; duel++){
            for (int prev = 0; prev < 2; prev++){
                if(!dp[duel-1][prev])
                    continue;
                // For each possible current outcome (cur ∈ {0,1}) in duel 'duel'
                for (int cur = 0; cur < 2; cur++){
                    // The player affected is player = duel (which is the (duel+1)-th player)
                    if(a[duel] == 0){
                        // Player must have 0 wins: win count = (!prev) + cur must equal 0.
                        // This forces: !prev==0 => prev==1 and cur==0.
                        if(prev == 1 && cur == 0)
                            dp[duel][cur] = true;
                    } else { // a[duel] == 1: need at least one win.
                        // The only forbidden case is (prev==1, cur==0) (which would give 0 wins).
                        if(prev == 1 && cur == 0)
                            continue;
                        dp[duel][cur] = true;
                    }
                }
            }
        }
        
        // Final check: verify player n (index n-1) condition 
        // Player n's win count is determined solely by the last duel outcome (duel index n-2).
        // If a[n-1]==0 then we need x[n-2]==1; if a[n-1]==1 then we need x[n-2]==0.
        bool assignmentExists = false;
        for (int cur = 0; cur < 2; cur++){
            // For n==2, dp[0] holds the only duel.
            if(n == 2){
                if(!dp[0][cur])
                    continue;
                if(a[1] == 0 && cur == 1)
                    assignmentExists = true;
                if(a[1] == 1 && cur == 0)
                    assignmentExists = true;
            } else {
                if(!dp[n-2][cur])
                    continue;
                if(a[n-1] == 0 && cur == 1)
                    assignmentExists = true;
                if(a[n-1] == 1 && cur == 0)
                    assignmentExists = true;
            }
        }
        
        // If a valid assignment exists then every report might hold (so answer "NO" because we can't prove a lie).
        // Otherwise, we print "YES" (we've found that at least one must be lying).
        cout << (assignmentExists ? "NO" : "YES") << "\n";
    }
    
    return 0;
}
