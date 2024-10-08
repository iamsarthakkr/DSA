#include <bits/stdc++.h>
using namespace std;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/cpp/templates/CompCoding/debug.cpp"
#else 
#define debug(...) 69
#endif

struct Segtree {
   struct Item {
      int min;
      int count;

      Item() { // empty element neutral
         min = INT_MAX;
         count = 0;
      }
      Item(int v) {  // single
         min = v;
         count = 1;
      }
   };
   int size;
   vector<Item> tree;

   const Item NETURAL_ELEMENT;

   Item merge(const Item& a, const Item& b) {
      Item res;
      res.min = min(a.min, b.min);
      if(a.min == res.min) res.count += a.count;
      if(b.min == res.min) res.count += b.count;
      return res;
   }

   Segtree(int n) {
      size = 1;
      while(size < n) size *= 2;
      tree.assign(2 * size, NETURAL_ELEMENT);
   }

   template<typename T>
   void build(int node, int lx, int rx, vector<T>& arr) {
      if(rx - lx == 1) {
         // leaf
         if(lx < (int)arr.size()) {
            tree[node] = { arr[lx] }; // single
         }
         return;
      }
      int m = (lx + rx) >> 1;
      build(2 * node + 1, lx, m, arr); 
      build(2 * node + 2, m, rx, arr);
      // recalc
      tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
   }

   template<typename T>
   void build(vector<T>& arr) {
      build(0, 0, size, arr);
   }

   // set operation
   template<typename T> 
   void set(int node, int lx, int rx, int i, T v) {
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
      // recalc
      tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
   }
   
   template<typename T>
   void set(int i, T v) {
      set(0, 0, size, i, v);
   }

   // calc operation
   Item calc(int node, int lx, int rx, int l, int r) {
      // disjoint
      if(rx <= l || r <= lx) {
         return NETURAL_ELEMENT;
      }
      // covered
      if(l <= lx && rx <= r) {
         return tree[node];
      }
      int m = (lx + rx) >> 1;
      auto s1 = calc(2 * node + 1, lx, m, l, r);
      auto s2 = calc(2 * node + 2, m, rx, l, r);
      return merge(s1, s2);
   }
   
   // function from l...r-1
   Item calc(int l, int r) {
      return calc(0, 0, size, l, r);
   }
};

void Main() {
   int n, m;
   cin >> n >> m;
   vector<int> a(n);
   for(auto& x: a) cin >> x;

   Segtree st(n);
   st.build(a);

   while(m--) {
      int t;
      cin >> t;
      if(t == 1) {
         int i, v;
         cin >> i >> v;
         st.set(i, v);
      } else {
         int l, r;
         cin >> l >> r;
         auto res = st.calc(l, r);
         cout << res.min << " " << res.count << '\n';
      }
   }
}

int main() {
	ios::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
	cout << setprecision(12) << fixed;
#ifdef SARTHAK_LOCAL
   freopen("./input.txt", "r", stdin); freopen("./output.txt", "w", stdout);
   clock_t start = clock();
#endif

   Main();
   
#ifdef SARTHAK_LOCAL
   clock_t end = clock();
   cerr << "Total Time: " << (double)(end - start) * 1e3 / CLOCKS_PER_SEC << "ms" << '\n';
#endif
   return 0;
}