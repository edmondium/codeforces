#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> ostream &operator<<(ostream &os, const vector<T> &as) { const int sz = as.size(); os << "["; for (int i = 0; i < sz; ++i) { if (i >= 256) { os << ", ..."; break; } if (i > 0) { os << ", "; } os << as[i]; } return os << "]"; }
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }
#define COLOR(s) ("\x1b[" s "m")

////////////////////////////////////////////////////////////////////////////////
template <unsigned M_> struct ModInt {
  static constexpr unsigned M = M_;
  unsigned x;
  constexpr ModInt() : x(0U) {}
  constexpr ModInt(unsigned x_) : x(x_ % M) {}
  constexpr ModInt(unsigned long long x_) : x(x_ % M) {}
  constexpr ModInt(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}
  constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_) {}
  ModInt &operator+=(const ModInt &a) { x = ((x += a.x) >= M) ? (x - M) : x; return *this; }
  ModInt &operator-=(const ModInt &a) { x = ((x -= a.x) >= M) ? (x + M) : x; return *this; }
  ModInt &operator*=(const ModInt &a) { x = (static_cast<unsigned long long>(x) * a.x) % M; return *this; }
  ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }
  ModInt pow(long long e) const {
    if (e < 0) return inv().pow(-e);
    ModInt a = *this, b = 1U; for (; e; e >>= 1) { if (e & 1) b *= a; a *= a; } return b;
  }
  ModInt inv() const {
    unsigned a = M, b = x; int y = 0, z = 1;
    for (; b; ) { const unsigned q = a / b; const unsigned c = a - q * b; a = b; b = c; const int w = y - static_cast<int>(q) * z; y = z; z = w; }
    assert(a == 1U); return ModInt(y);
  }
  ModInt operator+() const { return *this; }
  ModInt operator-() const { ModInt a; a.x = x ? (M - x) : 0U; return a; }
  ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }
  ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }
  ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }
  ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }
  template <class T> friend ModInt operator+(T a, const ModInt &b) { return (ModInt(a) += b); }
  template <class T> friend ModInt operator-(T a, const ModInt &b) { return (ModInt(a) -= b); }
  template <class T> friend ModInt operator*(T a, const ModInt &b) { return (ModInt(a) *= b); }
  template <class T> friend ModInt operator/(T a, const ModInt &b) { return (ModInt(a) /= b); }
  explicit operator bool() const { return x; }
  bool operator==(const ModInt &a) const { return (x == a.x); }
  bool operator!=(const ModInt &a) const { return (x != a.x); }
  friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
};
////////////////////////////////////////////////////////////////////////////////

constexpr unsigned MO = 998244353;
using Mint = ModInt<MO>;


// \prod (a0 x^p0 + a1 x^p1)
struct XorConvolve2Terms {
  int n;
  int base;
  vector<Mint> fss[2];
  XorConvolve2Terms() {}
  XorConvolve2Terms(int n_) : n(n_), base(0) {
    for (int u = 0; u < 2; ++u) fss[u].assign(1 << n, 1);
  }
  void add(int p0, int p1, Mint a0, Mint a1) {
    base ^= p0;
    fss[0][p0 ^ p1] *= (a0 + a1);
    fss[1][p0 ^ p1] *= (a0 - a1);
  }
  vector<Mint> run() {
    // *= fss[u][p] when |p \cap (higher bits)| == u (mod 2)
    for (int e = 0; e < n; ++e) {
      for (int o = 0; o < 1 << n; o += (1 << (e + 1))) for (int p0 = o; p0 < o + (1 << e); ++p0) {
        const int p1 = p0 | 1 << e;
        const Mint t00 = fss[0][p0];
        const Mint t01 = fss[0][p1];
        const Mint t10 = fss[1][p0];
        const Mint t11 = fss[1][p1];
        fss[0][p0] = t00 * t01;
        fss[0][p1] = t00 * t11;
        fss[1][p0] = t10 * t11;
        fss[1][p1] = t10 * t01;
      }
    }
    auto &fs = fss[0];
    for (int e = 0; e < n; ++e) {
      for (int o = 0; o < 1 << n; o += (1 << (e + 1))) for (int p0 = o; p0 < o + (1 << e); ++p0) {
        const int p1 = p0 | 1 << e;
        const Mint t0 = fs[p0];
        const Mint t1 = fs[p1];
        fs[p0] = t0 + t1;
        fs[p1] = t0 - t1;
      }
    }
    const Mint invTwo = Mint(1 << n).inv();
    for (int p = 0; p < 1 << n; ++p) fs[p] *= invTwo;
    for (int p = 0; p < 1 << n; ++p) if (p < (base ^ p)) swap(fs[p], fs[base ^ p]);
    return fs;
  }
};

vector<Mint> xorConvolveIntervalsLR(int n, const vector<int> &ls, const vector<int> &rs) {
  const int E = n;
  const int N = ls.size();
  const auto &A = ls;
  const auto &B = rs;
  // Mint ans = 0;
  vector<Mint> ans(1 << E, 0);
  for (int e = 0; e < E; ++e) {
    // free bits: [0, e)
    const int mask = (1 << e) - 1;
    const int m = E - 1 - e;
    // Mint way = 0;
    vector<Mint> way(1 << (m + 1), 0);
    for (int phase = 0; phase < 2; ++phase) {
      // phase = 1: do not choose interval to make free b bits
      // mod (z^2 - 1)
      for (const int z : {+1, -1}) {
        // (high, weight) 2-taku
        XorConvolve2Terms f(m);
        for (int i = 0; i < N; ++i) {
          const int hb = B[i] >> (e + 1);
          const int ha = A[i] >> (e + 1);
          Mint wb = +Mint(B[i] & mask) * ((B[i] >> e & 1) ? z : 1);
          Mint wa = -Mint(A[i] & mask) * ((A[i] >> e & 1) ? z : 1);
          if (phase == 0) {
            if (B[i] >> e & 1) wb += +Mint(1 << e);
            if (A[i] >> e & 1) wa += -Mint(1 << e);
          }
          f.add(hb, ha, wb, wa);
        }
        // way += (phase ? -1 : +1) * f.run()[0];
        const auto res = f.run();
        for (int h = 0; h < 1 << m; ++h) {
          way[h << 1] += (phase ? -1 : +1) * res[h];
          way[h << 1 | 1] += (phase ? -1 : +1) * z * res[h];
        }
      }
    }
    // way /= 2;
    // way /= (1 << e);
    // ans += way;
    const Mint coef = Mint(2).pow(-(1 + e));
    for (int h = 0; h < 1 << E; ++h) ans[h] += coef * way[h >> e];
  }
  return {ans};
}

int T, N, M;
vector<int> L, R;

int main() {
	scanf("%d",&T);
	for(int tc=0;tc<T;tc++){
		scanf("%d%d", &M, &N);
		L.resize(M);
		R.resize(M);
		for (int i = 0; i < M; ++i) {
		  scanf("%d%d", &L[i], &R[i]);
		  ++R[i];
		}
		
		const auto ans = xorConvolveIntervalsLR(N + 1, L, R);
		//for (int h = 0; h < 1 << N; ++h) {
		//  printf("%u\n", ans[h].x);
		//}
		unsigned totalxor=0;
		for (int h = 0; h < 1 << N; ++h) {
			totalxor^=(ans[h]*Mint(2).pow(h)).x;
		}
		 printf("%u\n", totalxor);
  }
  return 0;
}
