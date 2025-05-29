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
const int maxn = 1e6 + 10 ;
int a[maxn] , n , fen[maxn] ; 

void upd(int x){
    while(x <= n){
        fen[x]++;
        x += x&-x;
    }
}

int que(int x){
    int ans =0 ;
    while(x){
        ans += fen[x] ;
        x -= x&-x;
    }
    return ans ; 
}

int f(vector<int> x){
    rep(i , 0, n)fen[i] =0;
    int ans =0 ;
    per(i , sz(x)-1 , 0){
        ans += que(x[i]);
        upd(x[i]) ;
    }
    
    return ans ; 
}

signed main(){
    ios::sync_with_stdio(0) ; cin.tie(0);
    
    int T ;
    cin >> T ;
    
    while(T--){
        vector <int> a1 , a2 ; 
        
        cin >> n ;
        rep(i ,1 ,n){
            int x; cin >> x; 
            
            if (i%2==1) {
                a1.pb(x);
            } else {
                a2.pb(x);
            }
        }    
        
        bool v = (f(a1)%2 != f(a2)%2);
        
        sort(all(a1)); sort(all(a2));
        
        int x1 = 0, x2 =0;    
        
        rep (i ,1 , n) {
            if (i%2==1) {
                a[i] = a1[x1] ; x1++; 
            } else {
                a[i] = a2[x2] ; x2++;
            }
        }
        
        if (v) {
            swap(a[n] , a[n-2]) ;
        }
        
        rep(i ,1 ,n) cout << a[i] << " ";
        cout << "\n";
    }
}