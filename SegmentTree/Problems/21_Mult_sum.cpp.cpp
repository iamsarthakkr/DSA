#include <bits/stdc++.h>
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
*/

using namespace std;
// using namespace __gnu_pbds;

// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define forn(i, n) for(int i = 0; i < n; i++)
#define ford(i, n) for(int i = n - 1; i >= 0; i--)
#define for1(i, n) for(int i = 1; i <= n; i++)
#define forr(i, l, r) for(int i = l; i <= r; i++)
#define forrd(i, l, r) for(int i = r; i >= l; i--)
#define all(a) (a).begin(), (a).end()
#define len(a) (int)(a).size()

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/cpp/templates/CompCoding/debug.cpp"
#else 
#define debug(...) 69
#endif

template<typename T> bool cmin(T& a, T b) { return b < a ? a = b, 1 : 0; }
template<typename T> bool cmax(T& a, T b) { return b > a ? a = b, 1 : 0; }

template<typename T>
T gcd(T a, T b) {
   while (b) { a %= b; swap(a, b); }
   return a;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(696969);

template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
      T t = m / a;
      m -= t * a; swap(a, m);
      u -= t * v; swap(u, v);
   }
   assert(m == 1);
   return u;
}

template<int md> 
class Modular {
   static_assert(md > 0, "MOD must be positive");

public:
   Modular():v(0) {}

   template<typename T>
   Modular(T v_) {
      v = normalize(v_);
   }   

   constexpr static int mod() { return md; }

   const int& operator()() const { return v; }
   template<typename U> explicit operator U() const { return static_cast<U>(v); }

   Modular& operator += (const Modular& other) { v = normalize((int64_t)v + (int64_t)other.v); return *this; }
   Modular& operator -= (const Modular& other) { v = normalize((int64_t)v - (int64_t)other.v); return *this; }
   Modular& operator *= (const Modular& other) { v = normalize((int64_t)v * (int64_t)other.v); return *this; }
   Modular& operator /= (const Modular& other) { *this *= Modular(inverse(other.v, mod())); return *this; }

   template<typename U> Modular& operator += (const U& other) { return *this += Modular(other); }
   template<typename U> Modular& operator -= (const U& other) { return *this -= Modular(other); }
   template<typename U> Modular& operator *= (const U& other) { return *this *= Modular(other); }
   template<typename U> Modular& operator /= (const U& other) { return *this /= Modular(other); }

   Modular& operator ++ () { return *this += 1; }
   Modular& operator -- () { return *this -= 1; }

   Modular& operator ++ (int) { Modular result(*this); *this += 1; return result; }
   Modular& operator -- (int) { Modular result(*this); *this -= 1; return result; }

   Modular operator + () const { return Modular(v); }
   Modular operator - () const { return Modular(-v); }

   friend Modular operator + (const Modular& a, const Modular& b) { return Modular(a) += b; }
   friend Modular operator - (const Modular& a, const Modular& b) { return Modular(a) -= b; }
   friend Modular operator * (const Modular& a, const Modular& b) { return Modular(a) *= b; }
   friend Modular operator / (const Modular& a, const Modular& b) { return Modular(a) /= b; }

   template<typename U> friend Modular operator + (const Modular& a, const U& b) { return Modular(a) += b; }
   template<typename U> friend Modular operator - (const Modular& a, const U& b) { return Modular(a) -= b; }
   template<typename U> friend Modular operator * (const Modular& a, const U& b) { return Modular(a) *= b; }
   template<typename U> friend Modular operator / (const Modular& a, const U& b) { return Modular(a) /= b; }

   template<typename U> friend Modular operator + (const U& a, const Modular& b) { return Modular(a) += b; }
   template<typename U> friend Modular operator - (const U& a, const Modular& b) { return Modular(a) -= b; }
   template<typename U> friend Modular operator * (const U& a, const Modular& b) { return Modular(a) *= b; }
   template<typename U> friend Modular operator / (const U& a, const Modular& b) { return Modular(a) /= b; }

   friend bool operator == (const Modular& a, const Modular& b) { return a.v == b.v; }
   friend bool operator != (const Modular& a, const Modular& b) { return !(a == b); }

   template<typename U> friend bool operator == (const Modular& a, const U& b) { return a.v == Modular(b); }
   template<typename U> friend bool operator == (const U& a, const Modular& b) { return Modular(a) == b; }

   template<typename U> friend bool operator != (const Modular& a, const U& b) { return a.v != Modular(b); }
   template<typename U> friend bool operator != (const U& a, const Modular& b) { return Modular(a) != b; }

   friend bool operator < (const Modular& a, const Modular& b) { return a.v < b.v; }
   template<typename U> friend bool operator < (const Modular& a, const U& b) { return a < Modular(b); }
   template<typename U> friend bool operator < (const U& a, const Modular& b) { return Modular(a) < b; }

   friend bool operator <= (const Modular& a, const Modular& b) { return a.v <= b.v; }
   template<typename U> friend bool operator <= (const Modular& a, const U& b) { return a <= Modular(b); }
   template<typename U> friend bool operator <= (const U& a, const Modular& b) { return Modular(a) <= b; }

   friend bool operator > (const Modular& a, const Modular& b) { return a.v > b.v; }
   template<typename U> friend bool operator > (const Modular& a, const U& b) { return a > Modular(b); }
   template<typename U> friend bool operator > (const U& a, const Modular& b) { return Modular(a) > b; }

   friend bool operator >= (const Modular& a, const Modular& b) { return a.v >= b.v; }
   template<typename U> friend bool operator >= (const Modular& a, const U& b) { return a >= Modular(b); }
   template<typename U> friend bool operator >= (const U& a, const Modular& b) { return Modular(a) >= b; }

   friend std::ostream& operator << (std::ostream& out, const Modular& n) { return out << int(n); }
   friend std::istream& operator >> (std::istream& in, Modular& n) { int64_t v_; in >> v_; n = Modular(v_); return in; }

private:
   template<typename T>
   static int normalize(T x) {
      int v = static_cast<int>(x % mod());

      if(v < 0) v += mod();
      return v;
   }   

private:
   int v;
};

template<typename T, typename U>
T power(const T& base, const U& exp) {
   assert(exp >= 0);
   T x=base, res=1;
   U p=exp;
   while (p > 0) {
      if (p & 1) res*=x;
      x*=x;
      p>>=1;
   }
   return res;
}

template <int T>
std::string to_string(const Modular<T>& number) {
  return to_string(number());
}

constexpr int MOD = 1000000007;
using Mint = Modular<MOD>;

std::vector<Mint> fact(1, 1);
std::vector<Mint> inv_fact(1, 1);

/*
Mint C(int n, int k) {
   if (k < 0 || k > n) {
      return 0;
   }

   while((int)fact.size() < n + 1) {
      fact.push_back(fact.back() * (int)fact.size());
      inv_fact.push_back(1 / fact.back());
   }

   return fact[n] * inv_fact[k] * inv_fact[n - k];
}
*/


template<typename Info, typename Operation>
struct Segtree {
   int size;
   vector<Info> tree;

   Segtree(int n) {
      init(n);
   }

   Segtree(vector<Info>& info) {
      init((int)info.size());
      this->build(0, 0, size, info);
   }

   // set node i to v
   void set(int i, const Info& v) {
      setImpl(0, 0, size, i, v);
   }

   // Calculate function from l ... r-1
   Info calc(int l, int r) {
      return calcImpl(0, 0, size, l, r);
   }

   // Apply operation to a segment
   void apply(int l, int r, const Operation& operation) {
      applyImpl(0, 0, size, l, r, operation);
   };

   // Get node i
   Info get(int i) {
      return calc(i, i + 1);
   }

private:
   // set operation
   void setImpl(int node, int lx, int rx, int i, const Info& v) {
      if(rx - lx == 1) {
         tree[node] = v;
         return;
      }
      propagate(node, lx, rx);

      int m = (lx + rx) >> 1;
      if(i < m) {
         setImpl(2 * node + 1, lx, m, i, v);
      } else {
         setImpl(2 * node + 2, m, rx, i, v);
      }

      recalc(node, lx, rx);
   }

   // calc operation
   Info calcImpl(int node, int lx, int rx, int l, int r) {
      // disjoint
      if(rx <= l || r <= lx) {
         return Info();
      }
      // covered
      if(l <= lx && rx <= r) {
         return tree[node];
      }
      propagate(node, lx, rx);

      int m = (lx + rx) >> 1;
      auto s1 = calcImpl(2 * node + 1, lx, m, l, r);
      auto s2 = calcImpl(2 * node + 2, m, rx, l, r);

      return Info::merge(s1, s2);
   }

   void  applyImpl(int node, int lx, int rx, int l, int r, const Operation& operation) {
      // disjoint
      if(rx <= l || r <= lx) {
         return;
      }
      // covered
      if(l <= lx && rx <= r) {
         tree[node].apply(lx, rx, operation);
         return;
      }
      propagate(node, lx, rx);

      int m = (lx + rx) >> 1;
      applyImpl(2 * node + 1, lx, m, l, r, operation);
      applyImpl(2 * node + 2, m, rx, l, r, operation);

      recalc(node, lx, rx);
   };

private:
   void propagate(int node, int lx, int rx) {
      if(rx - lx == 1) {
         return;
      }
      int m = (lx + rx) >> 1;
      auto& us = tree[node];
      tree[2 * node + 1].apply(lx, m, us);
      tree[2 * node + 2].apply(m, rx, us);
      us.resetOperation();
   }

   void recalc(int node, int lx, int rx) {
      if(rx - lx == 1) {
         return;
      }

      Info::unite(tree[node], tree[2 * node + 1], tree[2 * node + 2]);
   }

private: 
   void init(int n) {
      size = 1;
      while(size < n) size *= 2;
      tree.assign(2 * size, Info());
   }

   void build(int node, int lx, int rx, vector<Info>& arr) {
      if(rx - lx == 1) {
         if(lx < (int)arr.size()) {
            tree[node] = arr[lx];
         }
         return;
      }

      int m = (lx + rx) >> 1;
      build(2 * node + 1, lx, m, arr); 
      build(2 * node + 2, m, rx, arr);

      recalc(node, lx, rx);
   }
};

/* Operation for segtree */
struct Operation {
   Mint mult;

   Operation() { // No operation
      mult = 1;
   }

   Operation(long long _mult) {
      mult = _mult;
   }

   void change(const Operation& other) {
      if(other == NO_OP) return;
      if(*this == NO_OP) mult = other.mult;
      else {
         mult *= other.mult;
      }
   }

   bool operator == (const Operation& other) const {
      return other.mult == mult;
   }

   static const Operation NO_OP;
};

/* No operation */
Operation const Operation::NO_OP;

/* Info for segtree */
struct Info {
public:
   Mint val;
   Operation operation;

public:
   Info() { // Neutral element
      val = 0;
      operation = Operation::NO_OP;
   }
   
   Info(long long v) { // single
      val = v;
      operation = Operation::NO_OP;
   }

   void resetOperation() {
      operation = Operation::NO_OP;
   }

   void apply(int lx, int rx, const Operation& to_apply) {
      if(to_apply == Operation::NO_OP) return;
   
      val *= to_apply.mult;
      operation.change(to_apply);
   };
   
   static void unite(Info& node, const Info& a, const Info& b) {
      node.val = a.val + b.val;
   }

   void apply(int lx, int rx, const Info& node) {
      apply(lx, rx, node.operation);
   };

   static Info merge(const Info& a, const Info& b) {
      Info res;
      unite(res, a, b);
      return res;
   }
};

/* usage -> Segtree<Info, Operation> st(infos) */

void Main() {
   int n, m;
   cin >> n >> m;

   vector<Info> infos(n, 1);
   Segtree<Info, Operation> st(infos);
   while(m--) {
      int t;
      cin >> t;
      if(t == 1) {
         int l, r, v;
         cin >> l >> r >> v;
         st.apply(l, r, {v});
      } else {
         int l, r;
         cin >> l >> r;
         auto nd = st.calc(l, r);
         cout << nd.val << '\n';
      }
   } 
}

#define MULTI 0	// 0 for single test case

int main() {
	ios::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	cout << setprecision(12) << fixed;
#ifdef SARTHAK_LOCAL
   clock_t start = clock();
#endif

	int tt = 1;
	if (MULTI) cin >> tt;

	for(int test_case = 1; test_case <= tt; test_case++) {
		debug(test_case);

		Main();
      // cout << Main() << '\n';
      // cout << (Main() ? "YES" : "NO") << '\n';

      #ifdef SARTHAK_LOCAL
         cerr << "----------------------------------------------------------------------------------------------------------------------------------------" << '\n';
      #endif
	}

#ifdef SARTHAK_LOCAL
   clock_t end = clock();
   cerr << "Total Time: " << (double)(end - start) * 1e3 / CLOCKS_PER_SEC << "ms" << '\n';
#endif
   return 0;
}