#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll N = 200 + 5, Inf = 0xcfcfcfcfcfcfcfcf;

inline ll sqr(ll x){
	return x * x;
}

inline ll gcd(ll x, ll y){
	if(y) return gcd(y, x % y);
	else return x;
}

inline void checkmax(ll &x, ll y){
	if(y > x) x = y;
}

ll n = 0, m = 0, magic = 0, w[N] = {}, c[N] = {};
ll f[N][N * N] = {}, g[N][N][N][2] = {};
vector<vector<ll> > G(N);

inline void main_min(){
	memset(f, 0xcf, sizeof(f));
	for(ll x = 0 ; x <= magic ; x ++) f[1][x] = 0;
	for(ll u = 1 ; u <= n ; u ++){
		for(ll x = 0 ; x + c[u] <= magic ; x ++) checkmax(f[u][x + c[u]], f[u][x] + w[u]);
		for(ll v : G[u]) for(ll x = 0 ; x <= magic ; x ++) checkmax(f[v][x], f[u][x]);
	}
}

inline void solve_max(ll i){
	ll a = c[i], b = w[i];
	for(ll x = 0 ; x < a ; x ++) g[i][1][x][0] = 0;
	for(ll u = 1 ; u <= n ; u ++){
		if(u == i) for(ll x = 0 ; x < a ; x ++) checkmax(g[i][u][x][1], g[i][u][x][0]);
		else if(w[u] * a > c[u] * b) memset(g[i][u], 0xcf, sizeof(g[i][u]));
		for(ll s = 0, k = gcd(c[u], a) ; s < k ; s ++) for(ll x = s, t = 0 ; t < 2 * (a / k) ; x = (x + c[u]) % a, t ++){
			checkmax(g[i][u][(x + c[u]) % a][0], g[i][u][x][0] + w[u] - ((x + c[u]) / a) * b);
			checkmax(g[i][u][(x + c[u]) % a][1], g[i][u][x][1] + w[u] - ((x + c[u]) / a) * b);
		}
		for(ll v : G[u]) for(ll x = 0 ; x < a ; x ++){
			checkmax(g[i][v][x][0], g[i][u][x][0]);
			checkmax(g[i][v][x][1], g[i][u][x][1]);
		}
	}
}

inline void main_max(){
	memset(g, 0xcf, sizeof(g));
	for(ll i = 1 ; i <= n ; i ++) solve_max(i);
}

int main(){
	scanf("%lld %lld", &n, &m);
	for(ll i = 1 ; i <= n ; i ++){
		scanf("%lld %lld", &c[i], &w[i]);
		magic = max(magic, sqr(c[i]));
	}
	for(ll i = 1, u = 0, v = 0 ; i <= m ; i ++){
		scanf("%lld %lld", &u, &v);
		G[u].push_back(v);
	}
	main_min(), main_max();
	ll q = 0, p = 0, r = 0;
	scanf("%lld", &q);
	while(q --){
		scanf("%lld %lld", &p, &r);
		if(r <= magic) printf("%lld\n", f[p][r]);
		else{
			ll ans = Inf;
			for(ll i = 1 ; i <= n ; i ++){
				ll a = c[i], b = w[i];
				checkmax(ans, g[i][p][r % a][1] + (r / a) * b);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}