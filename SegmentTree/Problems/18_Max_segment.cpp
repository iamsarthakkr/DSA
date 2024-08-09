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
   bool operator == (const Operation& other) const {
      return other.max == max;
   }

public:
   long long max;

   Operation() { // No operation
      max = 0;
   }

   Operation(long long _max) {
      max = _max;
   }

   static const Operation NO_OP;
};

/* No operation */
const Operation NO_OP = { int64_t(-2e9) };

/* Info for segtree */
struct Info {
public:
   long long val;
   Operation operation;

public:
   Info() { // Neutral element
      val = -2e9;
      operation = NO_OP;
   }
   
   Info(long long v) { // single
      val = v;
      operation = NO_OP;
   }

   void resetOperation() {
      operation = NO_OP;
   }

   void apply(int lx, int rx, const Operation& to_apply) {
      if(to_apply == NO_OP) return;

      val = max(val, to_apply.max);
      if(operation == NO_OP) {
         operation = to_apply;
      } else {
         operation.max = max(operation.max, to_apply.max);
      }
   };

   void apply(int lx, int rx, const Info& node) {
      apply(lx, rx, node.operation);
   };

   static Info merge(const Info& a, const Info& b) {
      Info res;
      unite(res, a, b);
      return res;
   }

   static void unite(Info& node, const Info& a, const Info& b) {
      node.val = max(a.val, b.val);
   }
};

/* usage -> Segtree<Info, Operation> st(infos) */

void Main() {
   int n, m;
   cin >> n >> m;
   vi a(n);

   vector<Info> infos(n, 0);
   Segtree<Info, Operation> st(infos);

   while(m--) {
      int t;
      cin >> t;
      if(t == 1) {
         int l, r, v;
         cin >> l >> r >> v;
         st.apply(l, r, { v });
      } else {
         int i;
         cin >> i;
         auto nd = st.get(i);
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