#include <bits/stdc++.h>
 
#define pb push_back
#define int long long 
#define F first
#define S second
#define sz(a) (int)a.size()
#define pii pair<int,int> 
#define rep(i , a , b) for(int i = (a) ; i <= (b) ; i++)
#define per(i , a , b) for(int i = (a) ; i >= (b) ; i--)
#define all(a) a.begin(),a.end() 
 
using namespace std ;
const int maxn = 5e5 + 10 , mod = 1e9 + 7;
int a[maxn] , ri[maxn] , le[maxn] , bl[maxn] , br[maxn] , sl[maxn] , sr[maxn] ;
 
 
signed main(){
    ios::sync_with_stdio(0) ; cin.tie(0);
    
    int T;
    cin >> T;
    
    while(T--) {
        int n; cin >> n; 
        
        rep(i ,1, n) {
            cin >> a[i];
        }    
        
        vector <int> s , b; 
        
        rep(i , 1 ,n){
            while(sz(s) && a[s.back()] > a[i])s.pop_back() ;
            while(sz(b) && a[b.back()] < a[i])b.pop_back() ;
            
            sl[i] = (sz(s) ? s.back() : 0);
            bl[i] = (sz(b) ? b.back() : 0);    
            s.pb(i); b.pb(i) ;
        }
        
        s.clear();
        b.clear(); 
        
        per(i , n , 1){
            while(sz(s) && a[s.back()] > a[i])s.pop_back() ;
            while(sz(b) && a[b.back()] < a[i])b.pop_back() ;
            sr[i] = (sz(s) ? s.back() : n+1);
            br[i] = (sz(b) ? b.back() : n+1);    
            s.pb(i); b.pb(i) ;    
        }
        
        ri[n] = n;
        per(i , n-1 ,1){
            ri[i] = ri[i+1];        
            if(a[i] > a[i+1] && a[br[i+1]] < a[i]){
                ri[i] = min(ri[i] , br[i+1]-1);
            }
            
            if(a[i] < a[i+1] && a[sr[i+1]] > a[i]){
                ri[i] = min(ri[i] , sr[i+1]-1);
            }
        }
        
        
        le[1] = 1 ;
        rep(i , 2,n){
            le[i] = le[i-1] ;
            if(a[i] > a[i-1] && a[bl[i-1]] < a[i]){
                le[i] = max(le[i] , bl[i-1]+1);
            }
            if(a[i] < a[i-1] && a[sl[i-1]] > a[i]){
                le[i] = max(le[i] , sl[i-1]+1);
            }
        }
        
        int ans = ri[1] ;     
        rep(i , 2 , n){
            ans = (ans + (i-1 - le[i] + 1) * (ri[i] - ri[i-1]) + ri[i]-i+1) ;
        }
        cout << ans << "\n" ; 
    }
}