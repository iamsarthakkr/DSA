#include <bits/stdc++.h>
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
*/
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

template<typename Info>
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

   // set operation
   void set(int node, int lx, int rx, int i, Info v) {
      if(rx - lx == 1) {
         // leaf
         tree[node] = v;
         return;
      }
      int m = (lx + rx) >> 1;
      if(i < m) {
         set(2 * node + 1, lx, m, i, v);
      } else {
         set(2 * node + 2, m, rx, i, v);
      }
      recalc(node, lx, rx);
   }
   
   void set(int i, Info v) {
      set(0, 0, size, i, v);
   }

   // calc operation
   Info calc(int node, int lx, int rx, int l, int r) {
      // disjoint
      if(rx <= l || r <= lx) {
         return Info();
      }
      // covered
      if(l <= lx && rx <= r) {
         return tree[node];
      }
      int m = (lx + rx) >> 1;
      auto s1 = calc(2 * node + 1, lx, m, l, r);
      auto s2 = calc(2 * node + 2, m, rx, l, r);
      return Info::merge(s1, s2);
   }
   
   // function from l...r-1
   Info calc(int l, int r) {
      return calc(0, 0, size, l, r);
   }

private:
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
         // leaf
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

struct Info {
   ll val;

   Info() { // Neutral element
      val = 0;
   }
   
   Info(ll v) { // single
      val = v;
   }

   static Info merge(const Info& a, const Info& b) {
      Info res;
      unite(res, a, b);
      return res;
   }

   static void unite(Info& node, const Info& a, const Info& b) {
      node.val = a.val + b.val;
   }
};

/* usage -> Segtree<Info> st(infos) */


void Main() {
   int n, m;
   cin >> n >> m;

   vll a(n);
   forn(i, n) cin >> a[i];

   vector<Info> infos(n);
   forn(i, n) infos[i] = {a[i]};

   Segtree<Info> st(infos);
   while(m--) {
      int t;
      cin >> t;
      if(t == 1) {
         int i, v;
         cin >> i >> v;
         st.set(i, Info(v));
      } else {
         int l, r;
         cin >> l >> r;
         auto res = st.calc(l, r);
         cout << res.val << '\n';
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