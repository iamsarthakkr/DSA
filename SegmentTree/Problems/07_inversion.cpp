#include <bits/stdc++.h>
using namespace std;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/cpp/templates/CompCoding/debug.cpp"
#else 
#define debug(...) 69
#endif

struct Info {
   int val;

   Info() { // empty element neutral
      val = 0;
   }
   
   Info(int v) {  // single
      val = v;
   }

   static Info merge(const Info& a, const Info& b) {
      Info res;
      res.val = a.val + b.val;
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
   int n;
   cin >> n;
   vector a(n, 0);
   for(int i = 0; i < n; i++) cin >> a[i];

   Segtree st(n + 2);
   vector<int> inv(n);
   for(int i = 0; i < n; i++) {
      inv[i] = st.calc(a[i] + 1, n + 2).val;
      st.set(a[i], 1);
   }

   for(int x: inv) cout << x << " ";
   cout << '\n';
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