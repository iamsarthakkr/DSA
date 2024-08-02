#include <bits/stdc++.h>
using namespace std;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/cpp/templates/CompCoding/debug.cpp"
#else 
#define debug(...) 69
#endif

struct Info {
   array<int, 40> cnt;
   long long inv;
   Info() { // empty element neutral
      inv = 0;
      cnt = {0};
   }
   
   Info(int v) {  // single
      inv = 0;
      cnt = {0};
      cnt[v]++;
   }

   static void merge(Info& to, const Info& a, const Info& b) {
      to.inv = a.inv + b.inv;
      for(int i = 0; i < 40; i++) {
         for(int j = i + 1; j < 40; j++) {
            to.inv += (long long)b.cnt[i] * a.cnt[j];
         }
         to.cnt[i] = a.cnt[i] + b.cnt[i];
      }
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
      Info::merge(tree[node], tree[2 * node + 1], tree[2 * node + 2]);
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
      Info res;
      Info::merge(res, s1, s2);
      return res;
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
      Info::merge(tree[node], tree[2 * node + 1], tree[2 * node + 2]);
   }
};

void Main() {
   int n, q;
   cin >> n >> q;
   vector<int> a(n);
   for(auto& x: a) {
      cin >> x;
      --x;   
   }
   debug(a);

   vector<Info> info;
   for(int i = 0; i < n; i++) info.emplace_back(a[i]);

   Segtree st(info);
   while(q--) {
      int t;
      cin >> t;
      if(t == 2) {
         int i, v;
         cin >> i >> v;
         --i; --v;
         st.set(i, v);
      } else {
         int l, r;
         cin >> l >> r;
         debug(l, r);
         --l;
         cout << st.calc(l, r).inv << '\n';
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