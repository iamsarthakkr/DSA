#include <bits/stdc++.h>
using namespace std;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/cpp/templates/CompCoding/debug.cpp"
#else 
#define debug(...) 69
#endif

struct Info {
   int max;

   Info() { // empty element neutral
      max = -INT_MAX;
   }
   
   Info(int v) {  // single
      max = v;
   }

   static Info merge(const Info& a, const Info& b) {
      Info res;
      res.max = std::max(a.max, b.max);
      return res;
   }
};

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

   int first_above(int x, int lx, int rx, int val, int l = 0) {
      if(tree[x].max < val || rx <= l) return -1;
      if(rx - lx == 1) {
         return lx;
      }
      int m = (rx + lx) >> 1;
      int i = first_above(2 * x + 1, lx, m, val, l);
      if(i == -1) i = first_above(2 * x + 2, m, rx, val, l);
      return i;
   }

   int first_above(int x, int l = 0) {
      return first_above(0, 0, size, x, l);
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
      tree[node] = Info::merge(tree[2 * node + 1], tree[2 * node + 2]);
   }
   
   template<typename T>
   void set(int i, T v) {
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
      // recalc
      tree[node] = Info::merge(tree[2 * node + 1], tree[2 * node + 2]);
   }
};

void Main() {
   int n, m;
   cin >> n >> m;
   vector<int> a(n);
   for(auto& x: a) cin >> x;

   vector<Info> info(n);
   for(int i = 0; i < n; i++) info[i] = Info(a[i]);

   Segtree st(info);

   while(m--) {
      int t;
      cin >> t;
      if(t == 1) {
         int i, v;
         cin >> i >> v;
         st.set(i, v);
      } else {
         int x;
         cin >> x;
         int l = 0;
         cin >> l;
         auto res = st.first_above(x, l);
         cout << res << '\n';
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